#include "node_item.h"
#include "sim_scene.h"
#include "mainwindow.h"

NodeItem::NodeItem (QString ip, qreal x, qreal y, qreal z, EnemyAttr ea, bool ct)
{
    alive = true;
    destroyRate = 0.0;
    ipAddr.setAddress(ip);
    x_coordinate = x;
    y_coordinate = y;
    z_coordinate = z;
    nodeship = ea;
    center = ct;
}

QRectF NodeItem::boundingRect() const
{
    if (!center)
    {
        return QRectF(-20, -20, 40, 40);
    }
    else
    {
        return QRectF(-30*cos(PI/10), -30, 60*cos(PI/10), 60+60*cos(PI/5));
    }
}

QPainterPath NodeItem::shape()
{
    QPainterPath path;
    if (!center){
        path.addEllipse(QPointF(0.0, 0.0), 20, 20);
    }
    else
    {
        path.moveTo(-30*cos(PI/10), -30*sin(PI/10));
        path.lineTo(30*cos(PI/10), -30*sin(PI/10));
        path.lineTo(-30*sin(PI/5), 30*cos(PI/5));
        path.lineTo(0.0f, -30.0f);
        path.lineTo(30*sin(PI/5), 30*cos(PI/5));
        path.lineTo(-30*cos(PI/10), -30*sin(PI/10));
        path.setFillRule(Qt::WindingFill);
    }
    return path;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->setRenderHint(QPainter::NonCosmeticDefaultPen, true);
    QPixmap pix;

    SimScene *scene = dynamic_cast <SimScene *> (this->scene());

    QFont font("Arial",20,QFont::Bold,true);
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(3);
    QPainterPath path;
    path.addEllipse(QPointF(0.0,0.0),20,20);
    QRect rect(-20, -20, 40, 40);

    if (!alive)
    {
        if (nodeship == ENEMY)
        {
            pix.load("Icons/enemy_damage.png");
        }
        else if(nodeship == FRIEND)
        {
            pix.load("Icons/friend_damage.png");
        }
        else
        {
            pix.load("Icons/neutral_damage.png");
        }

        painter->drawPixmap(-15, -15, 30, 30, pix);
    }
    else if (scene->getLauncher() == this)
    {
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawPath(path);
        painter->fillPath(path, Qt::darkMagenta);
        painter->drawText(rect, Qt::AlignCenter, getNodeID());
    }
    else if (scene->getTarget() == this)
    {
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawPath(path);
        painter->fillPath(path, Qt::darkGreen);
        painter->drawText(rect, Qt::AlignCenter, getNodeID());
    }
    else if (nodeship == ENEMY)
    {
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawPath(path);
        painter->fillPath(path, Qt::red);
        painter->drawText(rect, Qt::AlignCenter, getNodeID());
    }
    else if (nodeship == FRIEND)
    {
        if (center)
        {
            pix.load("Icons/star.png");
            painter->drawPixmap(-30, -30, 60, 60, pix);
        }
        else
        {
            /*
            pix.load("Icons/red.png");
            painter->drawPixmap(-10, -10, 20, 20, pix);
            */
            painter->setPen(pen);
            painter->setFont(font);
            painter->drawPath(path);
            painter->fillPath(path, Qt::blue);
            painter->drawText(rect, Qt::AlignCenter, getNodeID());
        }
    }
    else
    {
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawPath(path);
        painter->fillPath(path, Qt::black);
        painter->drawText(rect, Qt::AlignCenter, getNodeID());
    }
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!alive)
    {
        return;
    }

    SimScene *scene = dynamic_cast<SimScene *> (this->scene());
    MainWindow *mw = dynamic_cast<MainWindow *> (this->scene()->parent());

    if (event->button() == Qt::LeftButton)
    {
        if (center)
        {
            QMessageBox::warning(mw, QObject::tr("警告"), QObject::tr("控制中心无法进行攻击！"));
            return;
        }
        scene->setLauncher(this);
        mw->setObjectIp(ipAddr.toString());
    }
    else if (event->button() == Qt::RightButton)
    {
        if (center)
        {
            QMessageBox::warning(mw, QObject::tr("警告"), QObject::tr("控制中心无法被攻击！"));
            return;
        }
        scene->setTarget(this);
        mw->setTargetIp(ipAddr.toString());
    }
    scene->update(scene->viewRect());
}

int NodeItem::type() const
{
    return UserType+1;
}

bool NodeItem::judgeDamage()
{
    qreal rate = this->destroyRate;
    qreal rNum = qrand() % 100;

    if (rNum <= rate * 100)
    {
        return true;
    }
    else
    {
        return false;
    }
}
