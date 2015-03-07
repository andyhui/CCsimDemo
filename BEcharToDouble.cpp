#include <math.h>
#include "mainwindow.h"

void MainWindow::BintToChar(int inter, char buf[])
{
    int i = 0;
    for (i = 3; i >= 0; i--)
    {
        buf[i] = inter & 0xff;
        inter >>= 8;
    }
}

/* char convert to double */
double MainWindow::BEcharTOdouble(unsigned char buf[])
{
    double m;
    int sign = 0;

    /*符号位*/
    int a = (buf[0]&0x80)>>7;
    if(a == 0)
    {
        sign = 1;
    }
    else if(a == 1)
    {
        sign = -1;
    }

    /*指数*/
    int E = ((buf[0]&0x7F)<<4)+((buf[1]&0xF0)>>4)-1023;

    /*尾数*/
    long M = ((buf[1]&0x0F)*power(2,48))+(buf[2]*power(2,40))+\
            (buf[3]*power(2,32))+(buf[4]*power(2,24))+\
            (buf[5]*power(2,16))+(buf[6]*power(2,8))+buf[7];

    /*结果*/
    m = sign*(1+M*power(2,-52))*power(2,E);
    return m;
}

double MainWindow::power(double x ,int n)  //幂指函数
{
    int i;
    double p = 1;
    for(i=1; i<=abs(n); i++)
    {
        p = p*x;
    }

    if(n<0)  //负指数时取倒数
    {
        p = 1.0/p;
    }
    return p;
}

