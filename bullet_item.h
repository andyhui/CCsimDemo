/* Missile Item in SAGUI Simulation GraphicsScene */

#ifndef BULLET_ITEM_H
#define BULLET_ITEM_H

#include <QtGui>
#include "node_item.h"

class BulletItem : public QGraphicsItem, QObject
{
public:
    BulletItem(NodeItem *src, NodeItem *dest);

    /* Calculate the angle from PointF start to Pointf end */
    qreal CalculateAngle(QPointF start, QPointF end);

protected:
    /* Return the bounding rect of BulletItem */
    QRectF boundingRect() const;

    /* Return the shape path of BulletItem */
    QPainterPath shape();

    /* Paint BulletItem */
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    /* Timer function to draw animation */
    void timerEvent(QTimerEvent *event);

    /* Distinguish BulletItem with other QGraphicsItem */
    int type() const;

private:
    NodeItem *source;       /* The NodeItem that emit BulletItem */
    NodeItem *destination;  /* The NodeItem that BulletItem is to attact */
    int timerId;            /* Animation's Timer ID */
    qreal direction;        /* BulletItem's face direction */
};

#endif // BULLET_ITEM_H
