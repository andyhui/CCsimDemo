/* SAGUI Simulation Scene */

#ifndef SIM_SCENE_H
#define SIM_SCENE_H

#include "bullet_item.h"
#include "node_item.h"

class SimScene : public QGraphicsScene
{
public:
    SimScene(QString s, QObject *parent = 0);

    /* Search NodeItem by the IP */
    NodeItem *findNodeByIp(QString ipStr);

    /* Set BulletItem */
    void setBulletItem(BulletItem *bulletitem)
    {
        bullet = bulletitem;
    }

    /* Get BulletItem */
    BulletItem* getBulletItem()
    {
        return this->bullet;
    }

    /* Get Map's File Path */
    QString getBgPath()
    {
        return bgPath;
    }

    /* Set Map's File Path */
    void setBgPath(QString path)
    {
        bgPath = path;
    }

    /* Set Simulation Map Range */
    void setSimRange(QPointF tl, QPointF br)
    {
        TopLeft = tl;
        BottomRight = br;
        simWidth = fabsf(BottomRight.x() - TopLeft.x());
        simHeight = fabsf(BottomRight.y() - TopLeft.y());
    }

    /* Get Simulation Map's Width */
    qreal getSimWidth()
    {
        return this->simWidth;
    }

    /* Get Simulation Map's Height */
    qreal getSimHeight()
    {
        return this->simHeight;
    }

    /* Get Simulation Map's Top Left Point */
    QPointF getSimTopLeft()
    {
        return this->TopLeft;
    }

    /* Get Simulation Map's Bottom Right Point */
    QPointF getSimBottomRight()
    {
        return this->BottomRight;
    }

    /* Set Missile's Launch NodeItem */
    void setLauncher(NodeItem *node)
    {
        this->launcher = node;
    }

    /* Set Missile's Target NodeItem */
    void setTarget(NodeItem *node)
    {
        this->target = node;
    }

    /* Get Missile's Launch NodeItem */
    NodeItem* getLauncher()
    {
        return this->launcher;
    }

    /* Get Missile's Target NodeItem */
    NodeItem* getTarget()
    {
        return this->target;
    }

    /* Return the View's Rect */
    QRectF viewRect()
    {
        return QRectF(-views().at(0)->viewport()->width()/2, \
                      -views().at(0)->viewport()->height()/2, \
                      views().at(0)->viewport()->width(), \
                      views().at(0)->viewport()->height());
    }

protected:
    /* Draw the Scene's Background */
    void drawBackground(QPainter *painter, const QRectF &);

private:
    NodeItem *launcher; /* Missile's launch NodeItem */
    NodeItem *target;   /* Missile's target NodeItem */
    QPointF TopLeft;    /* Simulation Map's Top Left Point */
    QPointF BottomRight;/* Simulation Map's Bottom Right Point */
    qreal simWidth;     /* Simulation Map's Width */
    qreal simHeight;    /* Simulation Map's Height */
    BulletItem *bullet; /* Missile BulletItem */
    QString bgPath;     /* Map File's Path */
};

#endif // SIM_SCENE_H
