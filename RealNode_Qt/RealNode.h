#ifndef REALNODE_H
#define REALNODE_H

#include "Position.h"
#include "Message.h"

#include <QtGui>
#include <QtNetwork/QUdpSocket>

#define RECV_BIND_PORT 5555         /* setting the UDP bind port */

class RealNode : public QDialog
{
    Q_OBJECT
public:
    RealNode(QWidget *parent = 0,Qt::WindowFlags f=0);
    void initRealNode();                     /* initialize the GUI of real node */
    void randomPosition(Position *pos);      /* produce random position(x,y,z) */
    void respondAck(QByteArray byteArray);   /* respond ack back to control center */


private slots:
    void sendPosition();     /* timingly send position to control center */
    void handleCmd();        /* handle received message */
    void enableDiff();      /* diable diff */
    void okClicked();        /* ok button clicked,set UDP sending IP and port */
    void resetClicked();     /* reset button clicked, empty teh IP and port QLineText */


private:
    QUdpSocket sendSocket;    /*UDP send socket */
    QUdpSocket recvSocket;    /*UDP receive socket */

    QTimer sendTimer;        /* send timer */
    QTimer ackTimer;         /* ack timer */
    int xsign;                /* sign of computing x1*/
    int ysign;                /* sign of computing y1*/
    Position *position;      /* real node position */
    bool diff;               /* flag represents the received message in 2s if the same */
    QByteArray rcvDatagram;  /* current received message */
    QString strIP;           /* UDP send IP */
    QString strPort;         /* UDP send port */

    /* setting the initial position of realNode */
    QLabel* labX;
    QLabel* labY;
    QLabel* labZ;
    QLineEdit* leditX;
    QLineEdit* leditY;
    QLineEdit* leditZ;

    /* UDP IP and port */
    QLabel* labIP;
    QLabel* labPort;
    QLineEdit* leditIp;
    QLineEdit* leditPort;
    QPushButton* pbOK;
    QPushButton* pbReset;
    QPushButton* pbClose;
    QTextEdit* textEditCmd;     /* output the results of running */

};



#endif // REALNODE_H
