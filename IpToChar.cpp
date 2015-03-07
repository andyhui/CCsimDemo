
#include "mainwindow.h"

/* Function for storing IP eg: "127.0.0.1 " to "127000000001" */
void  MainWindow::IpToChar(char *inBuffer, int len, char *outBuffer)
{
       char* pCur = inBuffer;
       int pArr[4] = {0};
       int i = 0;
       int k = 0;
       pArr[i] = atoi(pCur);

       while(k++ < len)
       {
          if(*pCur == '.')
          {
               pArr[++i] = atoi(pCur + 1);
          }
          pCur++;

       }
       for( i = 0; i < 4; i ++)
       {
           outBuffer[i*3+0] = pArr[i]/100 + 48;
           outBuffer[i*3+1] = pArr[i]%100/10 + 48;
           outBuffer[i*3+2] = pArr[i]%10 + 48;
       }
}
