#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <QtGlobal>
#include <QByteArray>

class Message
{

 private:
    QByteArray virtualHeader;     /* CBR header */
    quint8 length;                /* message length */
    quint16 messageType;          /* message type */
    quint8 cordType;              /* cordination type */

 public:
    Message();
    void setHeader(QByteArray header);
    QByteArray getHeader();
    void setLength(quint8 len);
    quint8 getLength();
    void setMessageType(quint16 msgType);
    quint16 getMessageType();
    void setCordType(quint8 cordType);
    quint8 getCordType();

};

#endif // DATAGRAM_H
