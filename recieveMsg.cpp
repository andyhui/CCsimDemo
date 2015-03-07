#include "mainwindow.h"

void  MainWindow::recieveMsg()
{
    unsigned char recvBuffer[255]; /* Buffer for recieved message */
    quint64 maxSize = 255;   /* The max size of the recieved buffer */
    QHostAddress addr;  /* Address of opposite side  */
    quint16 port;  /* The outgoing port for recieved message */

    /* Zero out structure */
    memset(recvBuffer,0,sizeof(recvBuffer));

    /* Recieving the message */
    while(recvSocket.hasPendingDatagrams())
    {
        recvSocket.readDatagram((char*)recvBuffer,maxSize,&addr,&port);
    }

    /* Parse the recieved message */
    parseRecvMsg(recvBuffer,addr);
}
