#include "mainwindow.h"


qint64  MainWindow::getSendMsg(char sendBuffer[], QString str)
{
    /***
                            The command data struct
         ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         | cbr header(n bytes)|length (1byte)|type(2bytes)|data(12bytes)|
         ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ***/


    /***
                                               The CBR header
      +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      |source port(2 bytes)| type (1byte)|isMdpEnable(4 bytes)|seqNo(4 bytes)|txTime(8 bytes)|pktSize(4 bytes)|interval(8 bytes)|
      +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      ***/


    char dataBuffer[12]; /* Buffer for storing IP (except ".")*/
    qint64 size;        /* Size of send message */

    /* Put CBR header (source port) into send buffer */
    sendBuffer[1] = 5555 & 0xff;
    sendBuffer[0] = (5555 >> 8) & 0xff;

    /* Put CBR header (type) into send buffer */
    sendBuffer[2] = 'c';

    /* Put CBR header (isMdpEnable) into send buffer */
    char MdpBuffer[4];
    memset(MdpBuffer,0,sizeof(MdpBuffer));
    memcpy(sendBuffer+3,MdpBuffer,4);

    /* Put CBR header (seqNo) into send buffer */
    int temp = 1;
    char seqNoBuffer[4];
    memset(seqNoBuffer,0,sizeof(seqNoBuffer));
    BintToChar(temp,seqNoBuffer);
    memcpy(sendBuffer+7,seqNoBuffer,4);

    /* Put CBR header (txTime) into send buffer */
    QTime current_time = QTime::currentTime();
    quint64 second = current_time.second();

    int i;
    for ( i = 18; i >= 11;i--)
    {
        sendBuffer[i] = second & 0xff;
        second >>= 8;
    }

    /* Put CBR header (pktSize) into send buffer */
    int pktSize = 14;
    char pktSizeBuffer[4];
    memset(pktSizeBuffer,0,sizeof(pktSizeBuffer));
    BintToChar(pktSize,pktSizeBuffer);
    memcpy(sendBuffer+19,pktSizeBuffer,4);
    /* Put CBR header (interval) into send buffer */

    quint64 interval = 1;
    for ( i = 30; i >= 23;i--)
    {
        sendBuffer[i] = interval & 0xff;
        interval >>= 8;
    }
    /* Put length into send buffer */
    sendBuffer[32] = 14;

    /* Put type of message into send buffer */
    sendBuffer[34] = 0x11 & 0xff;
    sendBuffer[33] =(0x11 >> 8) & 0xff;

    /* Convert the QString to char* */
    char* inBuffer;

    QByteArray ba = str.toLatin1();

    inBuffer = ba.data();

    /* Zero out structure */
    memset (dataBuffer,0,sizeof(dataBuffer));

    /* Convert IP (include ".") to IP (except ".") */
    IpToChar(inBuffer,strlen(inBuffer),dataBuffer);

    /* Put IP into send buffer */
    memcpy(sendBuffer+35,dataBuffer,12);

    /* Get size of send message */
    size = 47;

    /* Return the Size */
    return size;
}
