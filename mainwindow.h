/* Main Window of SAGUI */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "node_item.h"
#include "bullet_item.h"
#include "sim_scene.h"
#include <QtNetwork>

#define SOUTHWEST_LATITUDE  31.862142
#define SOUTHWEST_LONGITUDE  118.790235
#define NORTHEAST_LATITUDE  31.8663105
#define NORTHEAST_LONGITUDE  118.7956085

#define SCENE_WIDTH 430
#define SCENE_HEIGHT 500

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    /* Create Window Menu */
    void createMenus();

    /* Read Initial Scene Settings of XML file */
    void initScenes(QString profilePath);
    void readBattleField();
    void readMapRange();
    void readNode();
    void skipUnknownElement();

    /* External Class Operate the SAGUI Widget */
    void setObjectIp(QString s);
    void setTargetIp(QString s);
    void appendResult(QString s);

    /* Message Sending and Recving */
    qint64 getSendMsg(char sendBuffer[255],QString str);
    void IpToChar(char* pBuffer,int len,char* ipBuffer);
    double BEcharTOdouble(unsigned char buf[8]);
    double power(double x ,int n);
    void parseRecvMsg(unsigned char recvBuffer[255],QHostAddress addr );
    void BintToChar(int inter,char buf[4]);

    /* Show the Missile Sending Animation */
    void sendMissile();

protected:
    bool eventFilter(QObject *, QEvent *);


public slots:
    void slotMap();         /* Change Map */
    void slotProfile();     /* Change Profile */
    void slotExit();        /* Quit SAGUI */

    void sendMsg();         /* Send Command */
    void cancelSelection(); /* Cancel Command */
    void recieveMsg();      /* Recv SA info and Command ack */

    void checkSend();       /* Check Send Operation */

private:
    QGraphicsView *saview;  /* To Show Simulation Scene */
    SimScene *scene;        /* Contains All GraphicsItem */

    QLineEdit *ccObjectLine;/* Show Command Object */
    QLineEdit *ccTargetLine;/* Show Command Target */
    QComboBox *ccTypeCombo; /* Select Command Type */
    QPushButton *sendButton;/* To Send Command */
    QPushButton *cancelButton;
                            /* To Cancel Command */
    QTextEdit *ccResultText;/* Show Command Result */

    QMenu *fileMenu;        /* File Menu of SAGUI */
    QAction *mapAction;     /* Action to Change Map */
    QAction *profileAction; /* Action to Change Profile */
    QAction *exitAction;    /* Action to Exit */

    QXmlStreamReader reader;/* To Read Profile of XML Format */

    QUdpSocket recvSocket;  /* Socket to Recv Data */
    QUdpSocket sendSocket;  /* Socket to Send Data */

    QTimer sendTimer;       /* Timer to Check if Send Successfully */
    bool cmdRet;            /* Mark Command Ack */
};

#endif // MAINWINDOW_H
