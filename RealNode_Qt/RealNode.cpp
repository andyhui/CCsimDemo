#include "RealNode.h"
#include "QApplication"

RealNode::RealNode(QWidget *parent,Qt::WindowFlags f) : QDialog(parent,f)
{

    qsrand(QTime::currentTime().second());

    /*initialize RealNode variables */
    initRealNode();

    /* bind the UDP receiving port:5555 */
    if(!recvSocket.bind(RECV_BIND_PORT))
    {
        QMessageBox::information(this,tr("error"),tr("UDP socket bind error!"));
        return;
    }

    connect(this->pbOK,SIGNAL(clicked()),this,SLOT(okClicked()));         /* ok button clicked,set the UDP IP and port */
    connect(this->pbReset,SIGNAL(clicked()),this,SLOT(resetClicked()));   /* reset button clicked,empty the IP and port QLineText*/
    connect(this->pbClose, SIGNAL(clicked()), this, SLOT(close()));       /* close button clicked,exit normally */
    connect(&sendTimer, SIGNAL(timeout()), this, SLOT(sendPosition()));   /* timingly send the real node position(x,y,z) to control center */
    connect(&recvSocket, SIGNAL(readyRead()), this, SLOT(handleCmd()));   /* receive control center instruction and handle it */

}
void RealNode::initRealNode()
{
    //initialize the variables
    this->diff = false;
    this->rcvDatagram = "";
    this->strIP = "";
    this->strPort = "";
    this->position = new Position();    /* initialize the position */
    this->xsign = 1;            /* initialize sign of computing x1 and y1 */
    this->ysign = 1;

    /* client layout */
    labX = new QLabel(tr("X"));
    leditX = new QLineEdit;
    labY = new QLabel(tr("Y"));
    leditY = new QLineEdit;
    labZ = new QLabel(tr("Z"));
    leditZ = new QLineEdit;
    labIP = new QLabel(tr("主机IP"));
    labPort = new QLabel(tr("端口号"));
    leditIp = new QLineEdit;
    leditPort = new QLineEdit;
    pbOK = new QPushButton(tr("开始"));
    pbReset = new QPushButton(tr("停止"));
    pbClose = new QPushButton(tr("退出"));
    textEditCmd = new QTextEdit();

    QGridLayout* gridlayoutUDP = new QGridLayout();
    gridlayoutUDP->addWidget(labIP,0,0);
    gridlayoutUDP->addWidget(leditIp,0,1);
    gridlayoutUDP->addWidget(labPort,1,0);
    gridlayoutUDP->addWidget(leditPort,1,1);

    QGridLayout* gridlayoutPosition = new QGridLayout();
    gridlayoutPosition->addWidget(labX,0,0);
    gridlayoutPosition->addWidget(leditX,0,1);
    gridlayoutPosition->addWidget(labY,1,0);
    gridlayoutPosition->addWidget(leditY,1,1);
    gridlayoutPosition->addWidget(labZ,2,0);
    gridlayoutPosition->addWidget(leditZ,2,1);

    QGroupBox* groupBoxUDP = new QGroupBox(tr("UDP配置"));
    QGroupBox* groupBoxPosition = new QGroupBox(tr("初始化坐标位置"));

    groupBoxUDP->setLayout(gridlayoutUDP);
    groupBoxPosition->setLayout(gridlayoutPosition);

    QGridLayout* gridlayoutLeft = new QGridLayout();
    gridlayoutLeft->addWidget(groupBoxUDP,0,0);
    gridlayoutLeft->addWidget(groupBoxPosition,1,0);
    gridlayoutLeft->addWidget(pbOK,2,0);
    gridlayoutLeft->addWidget(pbReset,3,0);
    gridlayoutLeft->addWidget(pbClose,4,0);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addLayout(gridlayoutLeft,0,0);
    mainLayout->addWidget(textEditCmd,0,1);

    setWindowTitle(QObject::tr("指控仿真平台-真实节点客户端"));
    this->setMaximumSize(600,1000);

}

/* send the random position(x,y,z) to the contro center */
void RealNode::sendPosition()
{

    QByteArray datagram("");
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);   //version problem

    /*set protocol message */
    Message *msg = new Message();
    msg->setMessageType(0x01);

    msg->setCordType(0x01);     /* position cordinate type,0x01:迪卡尔坐标系,ox02:经纬高度坐标系 */
    msg->setLength(27);
    out << msg->getHeader()<< msg->getLength() << msg->getMessageType()
        << msg->getCordType()  << this->position->getXcord()
        << this->position->getYcord() << this->position->getZcord();

    /* set UDP socket destination IP and port before send random position */
    if(NULL!=this->strIP || NULL!=this->strPort)
    {
        /* send random position to control center */
        sendSocket.writeDatagram(datagram.remove(0,4),datagram.size(),
                                 QHostAddress(this->strIP),this->strPort.toInt());

       /* print the position information in the QTextEdit */
        this->textEditCmd->append("send position("+position->toString()+
                                  ") to destination "+this->strIP+":"+this->strPort);

    }

    /* random position(x,y,z) */
    this->randomPosition(this->position);
}

/* receive instruction, parse and execute it,
 * then respond the execution result to control center
*/
void RealNode::handleCmd()
{
   /* receive instruction */
    QByteArray indatagram("");
    while (recvSocket.hasPendingDatagrams())
    {
        indatagram.resize(recvSocket.pendingDatagramSize());
        recvSocket.readDatagram(indatagram.data(),indatagram.size());
    }
    QDataStream in(&indatagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_8);

    /* parse instruction and respond ack back */
    respondAck(indatagram);

}

/* randomly produce position.x and position.y */
void RealNode::randomPosition(Position *pos)
{
    double vx=0.0,vy=0.0,x1=0.0,y1=0.0;

    /*randomly vx and vy */
    vx = (double)qrand()/(double)RAND_MAX*MOVE_STEP;   //[0,MOVE_STEP]
    vy = (double)qrand()/(double)RAND_MAX*MOVE_STEP;  // [0,MOVE_STEP]

     //  qDebug()<<vx<<" "<<vy;

    x1 = pos->getXcord();
    y1 = pos->getYcord();

     /* to make the node run randomly */
    double resign=2.0;   //change the sign if it's less than resign;
    if(vx<resign)
    {
         this->xsign *= -1;

    }
    if(vy<resign){

         this->ysign *= -1;
    }

    /* if x,y bigger than the maxArea ,then x,y reduce a number in[0,MOVE_STEP]
     * otherwise if x,y is smaller then the minArea, the add a number in[0,MOVE_STEP];
     */
    double maxArea = AREA_MAX-MOVE_STEP,minArea = AREA_MIN+MOVE_STEP;
    if(x1>maxArea)
    {
          this->xsign = -1;
    }

    if(y1>maxArea)
    {
          this->ysign = -1;
    }

    if(x1<minArea)
    {
          this->xsign = 1;
    }

    if(y1<minArea)
    {
          this->ysign = 1;
    }

    x1 = x1+this->xsign*vx;
    y1 = y1+this->ysign*vy;

    this->position->setXcord(x1);
    this->position->setYcord(y1);
    this->position->setZcord(0.0);

}

/* 1.judge if receive the same message in 2 seconds,
 * just handle the same message once in 2 seconds.
 * 2.parse received message type,if it is attack instruction,
 * then execute it;
 * 3.respond the execution result back;
*/
void RealNode::respondAck(QByteArray indatagram)
{
    /* if receive the same message between 2 seconds,
     * just respond ack once
    */
    if(rcvDatagram==indatagram)
    {
        diff = false;
        /* after 2 seconds,reset diff = false */
        connect(&ackTimer, SIGNAL(timeout()), this, SLOT(enableDiff()));
        ackTimer.start(2000);       //set timer interval 2 seconds
    }else{

        diff = true;
    }
    rcvDatagram = indatagram;

    /* if receive different message,respond ack to control center */
    if(diff)
    {
        bool attack = false;    /* flag if it has attacked */

       /* get the type of the instruction */
       char datagramType[2];
       datagramType[0] = indatagram.at(33);
       datagramType[1] = indatagram.at(34);

       /*judge the instruction if it is attack command */
       if(datagramType[0]==0 && datagramType[1]==17)
        {

            /* if it is attack command ,then printf the attacked
            * node's IP whick means attacking successfully
            */
           QByteArray dataIp = indatagram.remove(0,35);   /* remove the header of the instruction */

           /* get IP,eg: 192168001060 -> 192.168.1.60 */
          QByteArray standardIP("");
          quint8 i=0,countZero = 0;
          while (i<dataIp.size())
            {
                if(dataIp[i] != '0')
                {
                       standardIP.append(dataIp[i]);
                        for(int k=1;k<(3-countZero);k++)
                        {
                            standardIP.append(dataIp[i+k]);
                        }
                        if(i!=12)
                        {
                           standardIP.append('.');
                        }
                        i = i+3-countZero;
                        countZero=0;
                        continue;

                 }else{
                        countZero++;
                        if(countZero==3)   //if it is 000
                        {
                            standardIP.append(dataIp[i]);
                            //qDebug() << standardIP;
                        }
                  }
                i++;
                if((i%3 == 0) && (i!= 12))
                {
                    standardIP.append('.');
                    countZero = 0;
                }

              }

           /* output the attack result to QTextEdit */
           this->textEditCmd->append("Successfully attacked the node: "+standardIP);
           attack = true;

      }else{
           /* unrecognized datagram type */
          this->textEditCmd->append("Unrecognized Instruction......");
          attack = false;
    }

    /*combine the ack message and respond to control center */
    Message* msg = new Message();
    msg->setMessageType(0x81);   //ack message type is 0x81

    /* respond data,0x01 means attack successfully,0x02 means failed */
    quint8 msgData = 0;
    if(attack)
    {
        msgData = 0x01;
    }else{
        msgData = 0x02;
    }
    msg->setLength(sizeof(msg->getMessageType()+1));

    /* respond ack to the control center*/
    QByteArray outdatagram;
    QDataStream out(&outdatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << msg->getHeader() << msg->getLength() << msg->getMessageType() << msgData;

    if(this->strIP != NULL && this->strPort != NULL)
    {
         sendSocket.writeDatagram(outdatagram.remove(0,4),
                                 QHostAddress(this->strIP),
                                 this->strPort.toInt());
    }
 }
}

/* OK pushButton click slot,set the UDP IP and port */
void RealNode::okClicked()
{
  if(NULL==leditIp->text() || NULL==leditPort->text())
  {
       QMessageBox::information(this,tr("UDP初始化"),tr("请正确配置目标主机的IP与端口号"));
  }else{
      this->strIP = leditIp->text();
      this->strPort = leditPort->text();
  }

  if(NULL==leditX->text() || NULL==leditY->text()||NULL==leditZ)
  {
      QMessageBox::information(this,tr("坐标位置初始化"),tr("请正确配置节点的初始位置"));

  }else{

      this->position->setXcord(leditX->text().toDouble(0));
      this->position->setYcord(leditY->text().toDouble(0));
      this->position->setZcord(leditZ->text().toDouble(0));
  }
   sendTimer.start(1000);     //millisecond
}

/* reset pushButton slot,empty all the input Dialog and stop the timer */
void RealNode::resetClicked()
{
    /*
    this->leditIp->setText("");
    this->leditPort->setText("");
    this->leditX->setText("");
    this->leditY->setText("");
    this->leditZ->setText("");  */

    sendTimer.stop();
}

/* disable the diff flag which meas different message */
void RealNode::enableDiff()
{
    this->diff = true;
}


int main (int argc, char **argv)
{
    QApplication app(argc, argv);    
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));    //set GUI to support chinese
    RealNode realnode;
    realnode.show();
    return app.exec();
}
