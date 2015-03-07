#include "bullet_item.h"
#include "sim_scene.h"
#include "mainwindow.h"

BulletItem::BulletItem(NodeItem *src, NodeItem *dest)
{
    this->setPos(src->pos());   /* Set Start Position of Missile */

    /* Calculate Start Direction */
    direction = CalculateAngle(src->pos(), dest->pos());

    /* Set Missile's Source and Destination */
    this->source = src;
    this->destination = dest;

    /* Rotate the Missile to the Right Direction */
    rotate(direction);

    /* Start a 30ms Timer, get Timer's ID */
    timerId = startTimer(30);
}

QRectF BulletItem::boundingRect() const
{
    return QRectF(-9.0, -6.0, 18.0, 12.0);
}

QPainterPath BulletItem::shape()
{
    QPainterPath path;
    path.moveTo(-9.0, -6.0);
    path.lineTo(9.0, 0.0);
    path.lineTo(-9.0, 6.0);
    path.lineTo(-7.0, 0.0);
    path.lineTo(-9.0, -6.0);
    return path;
}

void BulletItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawPath(shape());
}

void BulletItem::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        SimScene *simscene = (SimScene *)(this->scene());

        if (simscene->getBulletItem() == NULL)
        {
            return;
        }

        /* If Missile Reaches Target */
        if (simscene->getBulletItem()->collidesWithItem(destination))
        {
            simscene->removeItem(this);     /* Remove BulletItem from Scene */
            simscene->setBulletItem(NULL);
            killTimer(timerId);             /* Kill the Animation Timer */
            timerId = 0;

            MainWindow *mw = (MainWindow *)(simscene->parent());

            if (destination->judgeDamage()) /* If Target Damaged */
            {
                mw->appendResult(destination->getIpAddr().toString() + \
                                     tr(" 被 ") + source->getIpAddr().toString() + tr(" 摧毁 "));
                destination->setDamaged();
            }

            simscene->setLauncher(NULL);
            simscene->setTarget(NULL);
            mw->setObjectIp("");
            mw->setTargetIp("");
            simscene->update(simscene->viewRect());
            return;
        }

        /* Missile Not Reach Target */
        QPointF start = this->pos();        /* Reset Missile Start */
        QPointF end = destination->pos();   /* Reset Missile End */

        rotate(-direction);                 /* Resume Missile Direction */
        direction = CalculateAngle(start, end);
        rotate(direction);                  /* Re-rotate Missile */

        /* Set New Missile Position */
        this->setPos(start.x()+3*cos(direction*PI/180.0), start.y()+3*sin(direction*PI/180.0));
    }
}

int BulletItem::type() const
{
    return UserType+2;
}

qreal BulletItem::CalculateAngle(QPointF start, QPointF end)
{
    int delta_y = start.y()-end.y();
    int delta_x = start.x()-end.x();

    qreal angle = 0.0;
    if (delta_x == 0)
    {
        if (delta_y > 0)
        {
            angle = -90.0;
        }
        else
        {
            angle = 90.0;
        }
    }
    if (delta_y == 0)
    {
        if (delta_x > 0)
        {
            angle = 180.0;
        }
        else
        {
            angle = 0.0;
        }
    }

    qreal k = (qreal)delta_y / (qreal)delta_x;
    if (delta_x < 0)
    {
        angle = atan(k)*180.0/PI;
    }
    else if (delta_x > 0)
    {
        angle = atan(k)*180.0/PI-180.0;
    }
    return angle;
}
