#include "node_item.h"
#include "sim_scene.h"
#include "mainwindow.h"

NodeItem::NodeItem (QString ip, qreal x, qreal y, qreal z, EnemyAttr ea, bool ct,int nodeItemId)
{
    alive = true;
    destroyRate = 0.0;
    ipAddr.setAddress(ip);
    x_coordinate = x;
    y_coordinate = y;
    z_coordinate = z;
    nodeship = ea;
    center = ct;
    nodeId = nodeItemId;
}

QRectF NodeItem::boundingRect() const
{
    if (!center)
    {
        return QRectF(-10, -10, 20, 20);
    }
    else
    {
        return QRectF(-20*cos(PI/10), -20, 40*cos(PI/10), 40+40*cos(PI/5));
    }
}

QPainterPath NodeItem::shape()
{
    QPainterPath path;
    if (!center){
        path.addEllipse(QPointF(0.0, 0.0), 10, 10);
    }
    else
    {
        path.moveTo(-20*cos(PI/10), -20*sin(PI/10));
        path.lineTo(20*cos(PI/10), -20*sin(PI/10));
        path.lineTo(-20*sin(PI/5), 20*cos(PI/5));
        path.lineTo(0.0f, -20.0f);
        path.lineTo(20*sin(PI/5), 20*cos(PI/5));
        path.lineTo(-20*cos(PI/10), -20*sin(PI/10));
        path.setFillRule(Qt::WindingFill);
    }
    return path;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->setRenderHint(QPainter::NonCosmeticDefaultPen, true);
    QPixmap pix;

    SimScene *scene = dynamic_cast <SimScene *> (this->scene());

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
        pix.load("Icons/attack.png");
        painter->drawPixmap(-10, -10, 20, 20, pix);
    }
    else if (scene->getTarget() == this)
    {
        pix.load("Icons/target.png");
        painter->drawPixmap(-10, -10, 20, 20, pix);
    }
    else if (nodeship == ENEMY)
    {
        //pix.load("Icons/blue.png");
        char buffer[MAX_BUFF_LENGTH];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"Icons/blue%d",this->getNodeId());

        pix.load(buffer);
        painter->drawPixmap(-10, -10, 20, 20, pix);
    }
    else if (nodeship == FRIEND)
    {
        if (center)
        {
            pix.load("Icons/star.png");
            painter->drawPixmap(-20, -20, 40, 40, pix);
        }
        else
        {
            //printf("the node id is %d\n",this->getNodeId());
            char buffer[MAX_BUFF_LENGTH];
            memset(buffer,0,sizeof(buffer));
            sprintf(buffer,"Icons/red0%d",this->getNodeId());

            pix.load(buffer);
            //pix.load("Icons/red.png");
            painter->drawPixmap(-10, -10, 20, 20, pix);
        }
    }
    else
    {
        pix.load("Icons/black.png");
        painter->drawPixmap(-10, -10, 20, 20, pix);
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
