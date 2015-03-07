#ifndef POSTION_H
#define POSTION_H

#define AREA_MAX 1500.0
#define AREA_MIN 0.0
#define MOVE_STEP 30.0

#include <QtGlobal>   /* for the qrand() function */
#include <QTime>
#include <math.h>

/* the real node position */
class Position{

private:
    double xcord;
    double ycord;
    double zcord;


public:
    Position();
    void setXcord(double x);
    void setYcord(double y);
    void setZcord(double z);
    double getXcord();
    double getYcord();
    double getZcord();
    QString toString();    /* return string of x,y,z */

};


#endif // POSTION_H
