#include "mainwindow.h"


/* Funtion for parsing the recieved data */
void  MainWindow::parseRecvMsg(unsigned char recvBuffer[],QHostAddress addr)
{


    /***
                                           The coordinate data
         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         |CBR header(n bytes)|length(1byte)|type(2 bytes)|coordinate type (char) |x (double)|y (double)|z(double)|
         +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      ***/

   /***
                                      The command ACK
         ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         |CBR header(n bytes)|length(1 byte)|type(2 bytes) |command result (char) |
         ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ***/



    //quint8 length;               /* The length for data */
    double xcod,ycod/*,zcod*/;       /* The node's coordinate */
    unsigned char tempBufferX[8];/* The temporary buffer for X coordinate */
    unsigned char tempBufferY[8];/* The temporary buffer for Y coordinate */
    unsigned char tempBufferZ[8];/* The temporary buffer for Z coordinate */
    quint16 type;                   /* The type of recieved data */
    char result;                  /* The command result */

    /* Get the length of data */
    //length = recvBuffer[32];

    /* Get the type of recieved data */
    type = quint16 (recvBuffer[34] + (recvBuffer[33] << 8));

    /* Get the command result */
    result  = recvBuffer[35];

    /* Put the X coordinate into temporary buffer */
    memcpy(tempBufferX,recvBuffer+36,8);

    /* Put the Y coordinate into temporary buffer */
    memcpy(tempBufferY,recvBuffer+44,8);

    /* Put the Z coordinate into temporary buffer */
    memcpy(tempBufferZ,recvBuffer+52,8);

    NodeItem *node  = new NodeItem();
    switch(type)
    {
       /* Recieved message is coordinates */
       case 0x01:

            /* Parse the X coordinate */
            xcod = BEcharTOdouble(tempBufferX);

            /* Parse the Y coordinate */
            ycod = BEcharTOdouble(tempBufferY);

            /* Parse the Z coordinate */
            //zcod = BEcharTOdouble(tempBufferZ);

            /* For debug */
            //qDebug() << " The nodes' coordinates are:"<< xcod << ycod << zcod;
            node = scene->findNodeByIp(addr.toString());
            if (node == NULL)
            {
                //QMessageBox::warning(this, tr("警告"),tr("没有此节点!"));
                return;
            }


            if (!node->isAlive())
                return;

            //change the place of node item .
            /*node->setPos(scene->width()*(xcod-scene->getSimTopLeft().x())\
            /(scene->getSimBottomRight().x()-scene->getSimTopLeft().x())-scene->width()/2,\
                        scene->height()*(ycod-scene->getSimTopLeft().y())\
            /(scene->getSimBottomRight().y()-scene->getSimTopLeft().y())-scene->height()/2);*/
            //printf("width is %lf\n",scene->width());
            //printf("height is %lf\n",scene->height());
            //printf("getSimBottomRight.x is %lf\n",scene->getSimBottomRight().x());
            //printf("getSimTopLeft.x is %lf\n",scene->getSimTopLeft().x());

            //printf("getSimBottomRight.y is %lf\n",scene->getSimBottomRight().y());
            //printf("getSimTopLeft.y is %lf\n",scene->getSimTopLeft().y());

            printf("xcod is %lf\n",xcod);
            printf("ycod is %lf\n",ycod);

            printf("xcod after change is %lf\n",600*(1-(xcod-31.862142)/(0.0041685))-300);
            printf("ycod after change is %lf\n",600*(ycod-118.790235)/(0.0053735)-300);


            //node->setPos(600*(xcod-SOUTHWEST_LATITUDE)/(NORTHEAST_LATITUDE - SOUTHWEST_LATITUDE)-300,\
                         //600*(ycod-SOUTHWEST_LONGITUDE)/(NORTHEAST_LONGITUDE - SOUTHWEST_LONGITUDE)-300);

            //huiwu_liu
            /*node->setPos(600*(1-(xcod-SOUTHWEST_LATITUDE)/(NORTHEAST_LATITUDE - SOUTHWEST_LATITUDE))-300,\
                                     600*(ycod-SOUTHWEST_LONGITUDE)/(NORTHEAST_LONGITUDE - SOUTHWEST_LONGITUDE)-300);*/

            //node->setPos(1400*(1-(xcod-SOUTHWEST_LATITUDE)/(NORTHEAST_LATITUDE - SOUTHWEST_LATITUDE))-500,\
            //                         500*(ycod-SOUTHWEST_LONGITUDE)/(NORTHEAST_LONGITUDE - SOUTHWEST_LONGITUDE)-500);
            if(node->getNodeID()=="4" || node->getNodeID()=="9")
            {

            }
            else
            {
                node->setPos(SCENE_HEIGHT*(ycod-SOUTHWEST_LONGITUDE)/(NORTHEAST_LONGITUDE - SOUTHWEST_LONGITUDE)-SCENE_HEIGHT/2,\
                                         (SCENE_WIDTH)*(1-(xcod-SOUTHWEST_LATITUDE)/(NORTHEAST_LATITUDE - SOUTHWEST_LATITUDE))-SCENE_WIDTH/2);

            }


            break;

        /* Recieved message is command ACK */
       case 0x81:
           switch(result)
           {
              /* The command result is successful */
              case char(0x01):
                 //QMessageBox::warning(this, tr("警告"),tr("攻击目标成功!"));
                 cmdRet = true;
                 sendMissile();
                 break;

              /* The command result is faliure */
              case char(0x02):
                   //QMessageBox::warning(this, tr("警告"),tr("攻击目标失败!"));
                  break;
              default:
                 QMessageBox::warning(this, tr("警告"),tr("指控结果类型错误!"));
                 break;
          }
           break;
       default:
       QMessageBox::warning(this, tr("警告"),tr("接收信息类型错误!"));
       break;
   }

}
