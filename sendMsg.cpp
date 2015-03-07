#include "mainwindow.h"
void  MainWindow::sendMsg()
{
    qint64 size;        /* Size of send meaasge */
    char sendBuffer[255]; /* Buffer for send message */
    int i = 0;

    /* Get the command object */
    NodeItem *src = scene->findNodeByIp(ccObjectLine->text());
    NodeItem *dest = scene->findNodeByIp(ccTargetLine->text());

    if(src == NULL)
    {
        QMessageBox::warning(this, tr("警告"), tr("指控对象不存在！"));
        return;
    }
    else if(dest == NULL)
    {
        QMessageBox::warning(this, tr("警告"), tr("攻击目标不存在！"));
        return;
    }
    else if (!dest->isAlive())
    {
        QMessageBox::warning(this, tr("警告"), tr("攻击目标已被摧毁。"));
        return;
    }
    else if (src->getNodeShip() == ENEMY)
    {
        QMessageBox::warning(this, tr("警告"), tr("指控对象为敌方阵营，不可操控！"));
        return;
    }
    else if (dest->getNodeShip() == FRIEND)
    {
        if (QMessageBox::warning(this, tr("警告"), tr("攻击目标为红军，是否确定?"), \
                                 QMessageBox::No|QMessageBox::Yes)\
                == QMessageBox::No)
        {
            return;
        }
    }

    scene->setLauncher(src);
    scene->setTarget(dest);
    scene->update(scene->viewRect());

    /* Get the command object's address */
    QString str = dest->getIpAddr().toString();

    memset(sendBuffer,0,sizeof(sendBuffer));

   /* Get size of send message */
    size = getSendMsg(sendBuffer,str);

    sendTimer.start(2000);

    /* Send message to real or virtual node */
    for ( i = 0; i < 1; i++)
    {
        sendSocket.writeDatagram(sendBuffer,size,QHostAddress(src->getIpAddr().toString()),5555);
        //sleep(0.2);
    }
}
