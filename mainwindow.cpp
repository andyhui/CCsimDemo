#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(tr("指控仿真演示"));

    scene = new SimScene("Maps/c4istarlab.png", this);    /* New a Scene with Specified Map */
    //huiwu_liu
    scene->setSceneRect(-SCENE_WIDTH/2, -SCENE_HEIGHT/2, SCENE_WIDTH, SCENE_HEIGHT);      /* Set Scene Rect */

    saview = new QGraphicsView;                     /* New a View to Display Scene */
    saview->setScene(scene);                        /* Bind View to Scene */
    //huiwu_liu
    saview->setFixedSize(SCENE_WIDTH+40, SCENE_HEIGHT+40);
    //saview->setFixedSize(640, 640);                 /* Set View Size */
    saview->setAlignment(Qt::AlignCenter);          /* Set View Alignment */
    saview->show();                                 /* Show the View */

    ccObjectLine = new QLineEdit;
    ccTargetLine = new QLineEdit;
    ccResultText = new QTextEdit;
    sendButton = new QPushButton(tr("发布"));
    cancelButton = new QPushButton(tr("撤销"));

    ccTypeCombo = new QComboBox;
    ccTypeCombo->addItem(tr("攻击"));

    ccObjectLine->installEventFilter(this);
    ccTargetLine->installEventFilter(this);
    sendButton->installEventFilter(this);

    fileMenu = new QMenu(tr("文件"));
    mapAction = new QAction(tr("选择地图"), this);
    profileAction = new QAction(tr("选择想定"), this);
    exitAction = new QAction(tr("退出"), this);

    /* Create SAGUI Menus */
    createMenus();

    /* Load the Initial Data to Scene */
    initScenes("Profiles/profile.xml");

    /* Layout SAGUI Widget */
    QGroupBox *ccGroup = new QGroupBox(tr("指控发布"));
    QGridLayout *groupLayout = new QGridLayout(ccGroup);
    groupLayout->addWidget(new QLabel(tr("指控类型：")), 0, 0, 1, 1);
    groupLayout->addWidget(ccTypeCombo, 1, 0, 1, 2);
    groupLayout->addWidget(new QLabel(tr("指控对象：")), 2, 0, 1, 1);
    groupLayout->addWidget(ccObjectLine, 3, 0, 1, 2);
    groupLayout->addWidget(new QLabel(tr("指控目标：")), 4, 0, 1, 1);
    groupLayout->addWidget(ccTargetLine, 5, 0, 1, 2);
    groupLayout->addWidget(cancelButton, 6, 0, 1, 1);
    groupLayout->addWidget(sendButton, 6, 1, 1, 1);
    groupLayout->addWidget(new QLabel(tr("指控结果：")), 7, 0, 1, 1);
    groupLayout->addWidget(ccResultText, 8, 0, 1, 2);
    groupLayout->setSpacing(15);
    groupLayout->setMargin(10);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(saview, 3);
    mainLayout->addWidget(ccGroup, 1);

    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainWidget->setLayout(mainLayout);

    /* Bind Recv Port */
    recvSocket.bind(5824);

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelSelection()));
    connect(&recvSocket, SIGNAL(readyRead()), this, SLOT(recieveMsg()));
    connect(&sendTimer, SIGNAL(timeout()), this, SLOT(checkSend()));

    cmdRet = false;
}

MainWindow::~MainWindow()
{

}

void MainWindow::setObjectIp(QString s)
{
    ccObjectLine->setText(s);
}

void MainWindow::setTargetIp(QString s)
{
    ccTargetLine->setText(s);
}

void MainWindow::createMenus()
{
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(mapAction);
    connect(mapAction, SIGNAL(triggered()), this, SLOT(slotMap()));

    fileMenu->addAction(profileAction);
    connect(profileAction, SIGNAL(triggered()), this, SLOT(slotProfile()));

    fileMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void MainWindow::slotMap()
{
    QString s = QFileDialog::getOpenFileName(this, tr("选择地图文件"), "./Maps", \
                "png files (*.png);;jpg files (*.jpg);;jpeg files (*.jpeg);;bmp files (*.bmp)");
    if (s != NULL){
        scene->setBgPath(s);
        scene->update(scene->viewRect());
    }
}

void MainWindow::slotProfile()
{
    QString s = QFileDialog::getOpenFileName(this, tr("选择想定文件"), "./Profiles", \
                "xml files (*.xml)");
    initScenes(s);
}

void MainWindow::slotExit()
{
    this->close();
}

void MainWindow::sendMissile()
{
    NodeItem *src = scene->getLauncher();
    NodeItem *dest = scene->getTarget();

    if (src != NULL && dest != NULL)
    {
        if (scene->getBulletItem() != NULL)
        {
            //QMessageBox::warning(this, tr("警告"), tr("导弹已发射"));
            return;
        }

        scene->setLauncher(src);
        scene->setTarget(dest);
        scene->update(scene->viewRect());
        BulletItem *bullet = new BulletItem(src, dest);
        scene->addItem(bullet);
        scene->setBulletItem(bullet);

        ccResultText->append(src->getIpAddr().toString() + tr(" 攻击 ") + dest->getIpAddr().toString());
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("指控目标或对象不存在！"));
    }
}

void MainWindow::initScenes(QString profilePath)
{
    scene->clear();
    scene->setBulletItem(NULL);
    scene->update(scene->viewRect());
    ccObjectLine->clear();
    ccTargetLine->clear();
    ccResultText->clear();
    scene->setLauncher(NULL);
    scene->setTarget(NULL);

    if (profilePath != NULL)
    {
        QFile file(profilePath);

        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"Can't Open file: "<<profilePath;
            return;
        }

        reader.setDevice(&file);

        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                if (reader.name() == "battlefield")
                {
                    readBattleField();
                }
                else
                {
                    qDebug()<<"This is not a battlefield profile: "<<profilePath;
                    return;
                }
            }
            else
            {
                reader.readNext();
            }
        }
    }

    QPen pen;
    pen.setColor(Qt::white);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(1);
    //scene->addLine(-SCENE_WIDTH/2, SCENE_HEIGHT/2, SCENE_WIDTH/2, SCENE_HEIGHT/2, pen);
   // scene->addLine(-SCENE_WIDTH/2, -SCENE_HEIGHT/2, -SCENE_WIDTH/2-, -230, pen);
    //scene->addLine(-225, -250, -215, -230, pen);
   // scene->addLine(-225, 0, -245, 0, pen);
   // scene->addLine(-225, 250, -225, -250, pen);
   // scene->addLine(225, 250, 205, 240, pen);
   // scene->addLine(225, 250, 205, 260, pen);
   // scene->addLine(0, 225, 0, 245, pen);

   /* QGraphicsTextItem *text1 = \
            scene->addText(tr("(") + QString::number(scene->getSimTopLeft().x()) + \
                                             tr(",") + QString::number(scene->getSimBottomRight().y()) + \
                                              tr(")"));
    text1->setPos(-270, 250);
    text1->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *text2 = \
            scene->addText(tr("(") + QString::number(scene->getSimTopLeft().x()) + \
                                              tr(",") + QString::number((scene->getSimTopLeft().y() + \
                                                                         scene->getSimBottomRight().y())/2) + \
                                              tr(")"));
    text2->setPos(-220, -10);
    text2->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *text3 = scene->addText(tr("(") + QString::number((scene->getSimTopLeft().x() + \
                                                                        scene->getSimBottomRight().x())/2) + \
                                              tr(",") + QString::number(scene->getSimBottomRight().y()) + \
                                              tr(")"));
    text3->setPos(-25, 220);
    text3->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *text4 = scene->addText(QString::number(scene->getSimHeight()) + tr(" m"));
    text4->setPos(-215, -250);
    text4->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *text5 = scene->addText(QString::number(scene->getSimWidth()) + tr(" m"));
    text5->setPos(200, 220);
    text5->setDefaultTextColor(Qt::white);*/
}

/* Read XML Profile's battlefield Element */
void MainWindow::readBattleField()
{
    reader.readNext();

    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }
        else if (reader.isStartElement())
        {
            if (reader.name() == "MapRange")
            {
                QString rangeString = reader.readElementText();
                QStringList rangeList = rangeString.split(",", QString::SkipEmptyParts);
                if (rangeList.count() == 4)
                {
                    //set the sim_scene size
                    scene->setSimRange(QPointF(rangeList.at(0).toFloat(),\
                                               rangeList.at(1).toFloat()),\
                                       QPointF(rangeList.at(2).toFloat(),\
                                               rangeList.at(3).toFloat()));
                }
                else
                {
                    qDebug()<<"Invalid Map Range: "<<rangeString;
                }

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "Node")
            {
                readNode();
            }
            else
            {
                skipUnknownElement();
            }
        }
        else
        {
            reader.readNext();
        }
    }
}

/* Read XML Profile's Node Element */
void MainWindow::readNode()
{
    reader.readNext();
    NodeItem *node = new NodeItem;

    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }
        else if (reader.isStartElement())
        {
            //huiwu_liu
            if (reader.name() == "ID")
            {
                QString nodeItemId = reader.readElementText();
                //printf("the node id is %d\n",nodeItemId.toInt());
                node->setNodeId(nodeItemId.toInt());

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "IP")
            {
                QString ipAddr = reader.readElementText();
                node->setIpAddr(ipAddr);
                //printf("the node ip addr is \n");

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "Location")
            {
                QString locString = reader.readElementText();
                QStringList locList = locString.split(",", QString::SkipEmptyParts);
                if (locList.count() == 3)
                {
                    qreal Xcod = locList.at(0).toFloat();
                    qreal Ycod = locList.at(1).toFloat();
                    qreal Zcod = locList.at(2).toFloat();
                    node->setCooridate(Xcod, Ycod, Zcod);
                    node->setPos(SCENE_WIDTH*(Xcod-scene->getSimTopLeft().x())\
                /(scene->getSimBottomRight().x()-scene->getSimTopLeft().x())-SCENE_WIDTH/2,\
                                 SCENE_HEIGHT*(Ycod-scene->getSimTopLeft().y())\
                /(scene->getSimBottomRight().y()-scene->getSimTopLeft().y())-SCENE_HEIGHT/2);
                }
                else
                {
                    qDebug()<<"Invalid Location: "<<locString;
                }

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "Friendship")
            {
                QString friendString = reader.readElementText();
                if (friendString == "friend")
                {
                    node->setNodeShip(FRIEND);
                }
                else if (friendString == "neutral")
                {
                    node->setNodeShip(NEUTRAL);
                }
                else if (friendString == "enemy")
                {
                    node->setNodeShip(ENEMY);
                }

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "DestroyRate")
            {
                node->setDestroyRate(reader.readElementText().toFloat());

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else if (reader.name() == "Center")
            {
                QString flag = reader.readElementText();
                if (flag == "Yes")
                {
                    node->setCenter(true);
                }
                else
                {
                    node->setCenter(false);
                }

                if (reader.isEndElement())
                {
                    reader.readNext();
                }
            }
            else
            {
                skipUnknownElement();
            }
        }
        else
        {
            reader.readNext();
        }
    }
    scene->addItem(node);
    node->setToolTip(node->getIpAddr().toString());
}

/* Skip XML Profile's Unknown Element */
void MainWindow::skipUnknownElement()
{
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }
        else if (reader.isStartElement())
        {
            skipUnknownElement();
        }
        else
        {
            reader.readNext();
        }
    }
}

void MainWindow::appendResult(QString s)
{
    ccResultText->append(s);
}

void MainWindow::checkSend()
{
    if(!cmdRet)
    {
        ccResultText->append(tr("指控命令发布失败！"));
        scene->setLauncher(NULL);
        scene->setTarget(NULL);
        scene->update(scene->viewRect());
    }
    sendTimer.stop();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        //qDebug()<<event->type()<<target;
        QKeyEvent *keyEvent = static_cast <QKeyEvent *> (event);
        //qDebug("Key Value: %x\n", keyEvent->key());
        if (keyEvent->key() == Qt::Key_Return)
        {
            //qDebug()<<target;
            if (target == ccObjectLine)
            {
                NodeItem *object = scene->findNodeByIp(ccObjectLine->text());
                if (object != NULL)
                {
                    scene->setLauncher(object);
                    scene->update(scene->viewRect());
                    ccTargetLine->setFocus();
                }
                else
                {
                    QMessageBox::warning(this, tr("警告"), tr("指控对象不存在!"));
                }
            }
            else if (target == ccTargetLine)
            {
                NodeItem *target = scene->findNodeByIp(ccTargetLine->text());
                if (target != NULL)
                {
                    scene->setTarget(target);
                    scene->update(scene->viewRect());
                    sendButton->setFocus();
                }
                else
                {
                    QMessageBox::warning(this, tr("警告"), tr("攻击目标不存在!"));
                }
            }
            else if (target == sendButton)
            {
                sendMsg();
                ccObjectLine->clear();
                ccTargetLine->clear();
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::cancelSelection()
{
    scene->setLauncher(NULL);
    scene->setTarget(NULL);
    scene->update(scene->viewRect());
    ccObjectLine->clear();
    ccTargetLine->clear();
}
