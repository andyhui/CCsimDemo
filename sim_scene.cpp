#include "sim_scene.h"

SimScene::SimScene(QString s, QObject *parent) : QGraphicsScene(parent)
{
    bgPath = s;
    bullet = NULL;
    simWidth = simHeight = 0.0;
    launcher = target = NULL;
    qsrand(QTime::currentTime().msec());
}

void SimScene::drawBackground(QPainter *painter, const QRectF &)
{
    QPixmap map;
    if(!map.load(bgPath))
    {
        //qDebug()<<"bgPath:"<<bgPath<<"Read Fail!";
    }
    painter->drawPixmap(viewRect(), map, map.rect());
}

NodeItem* SimScene::findNodeByIp(QString ipStr)
{
    //qDebug()<<ipStr;

    QList <QGraphicsItem *> nodeList = items(); /* Get Scene's Item List */

    int count = nodeList.count();               /* Get Item Number */

    for (int i = 0; i < count; i++)             /* Search Through Items */
    {
        NodeItem *node = (NodeItem *)(nodeList.at(i));

        /* If Item Belongs to NodeItem */
        if (node->type() == QGraphicsItem::UserType + 1)
        {
            if (node->getIpAddr().toString() == ipStr)
            {
                //qDebug()<<node->getNodeShip();
                return node;
            }
        }
    }

    return NULL;
}
