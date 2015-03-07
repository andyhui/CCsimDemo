#include "Message.h"

Message::Message()
{
    QByteArray tempbArray(32,'h');    /* initialize the CBR header with 32 char 'h' */
    this->virtualHeader = tempbArray;
    this->length = 0;
    this->messageType = 0;
    this->cordType = 0;
}

void Message::setHeader(QByteArray header)
{
    this->virtualHeader = header;
}

QByteArray Message::getHeader()
{
   return this->virtualHeader;
}
void Message::setLength(quint8 len)
{
   this->length = len;
}
quint8 Message::getLength()
{
   return this->length;
}
void Message::setMessageType(quint16 msgType)
{
    this->messageType = msgType;
}
quint16 Message::getMessageType()
{
    return this->messageType;
}
void Message::setCordType(quint8 cordType)
{
    this->cordType = cordType;
}
quint8 Message::getCordType()
{
    return this->cordType;
}
