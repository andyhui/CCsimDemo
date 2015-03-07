#include "Position.h"

Position::Position()
{
      this->xcord = 0.0;
      this->ycord = 0.0;
      this->zcord = 0.0;
}

void Position::setXcord(double x)
{
    this->xcord = x;
}

void Position::setYcord(double y)
{
    this->ycord = y;
}
void Position::setZcord(double z)
{
    this->zcord = z;
}
double Position::getXcord()
{
    return this->xcord;
}
double Position::getYcord()
{
   return this->ycord;
}
double Position::getZcord()
{
   return this->zcord;
}

/* toString the Position */
QString Position::toString()
{
    return QString::number(this->getXcord())+","+
           QString::number(this->getYcord())+","+
           QString::number(this->getZcord());

}
