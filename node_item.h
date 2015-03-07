/* Battle Node Item in SAGUI Simulation GraphicsScene */

#ifndef NODE_ITEM_H
#define NODE_ITEM_H

#include <QtGui>
#include <QtNetwork/QHostAddress>

#define PI 3.141592653

/* Attribute of Enemy or Friend */
enum EnemyAttr
{
    FRIEND,
    ENEMY,
    NEUTRAL
};

class NodeItem : public QGraphicsItem
{
public:
    NodeItem(QString ip = "0.0.0.0", qreal x = 0.0, qreal y = 0.0, qreal z = 0.0, \
             EnemyAttr ea = FRIEND, bool ct = false);

    /* Check if Damaged */
    bool judgeDamage();

    /* Set Node Id */
    void setNodeID(QString id)
    {
        this->nodeId = id;
    }

    /* Get Node Id */
    QString getNodeID()
    {
        return this->nodeId;
    }

    /* Get Enemy Attribute */
    EnemyAttr getNodeShip()
    {
        return this->nodeship;
    }

    /* Set Enemy Attribute */
    void setNodeShip(EnemyAttr ea)
    {
        nodeship = ea;
    }

    /* Check if alive */
    bool isAlive()
    {
        return this->alive;
    }

    /* Set to be Damaged */
    void setDamaged()
    {
        this->alive = false;
    }

    /* Get IP Address */
    QHostAddress getIpAddr()
    {
        return this->ipAddr;
    }

    /* Set IP Address */
    void setIpAddr(QString ip)
    {
        ipAddr.setAddress(ip);
    }

    /* Get X Coordinate */
    qreal getXCoordinate()
    {
        return this->x_coordinate;
    }

    /* Get Y Coordinate */
    qreal getYCoordinate()
    {
        return this->y_coordinate;
    }

    /* Get Z Coordinate */
    qreal getZCoordinate()
    {
        return this->z_coordinate;
    }

    /* Set Coordinate */
    void setCooridate(qreal x, qreal y, qreal z)
    {
        this->x_coordinate = x;
        this->y_coordinate = y;
        this->z_coordinate = z;
    }

    /* Get Destroy Probability of being attacked */
    double getDestroyRate()
    {
        return this->destroyRate;
    }

    /* Set Destroy Probability of being attacked */
    void setDestroyRate(qreal rate){
        destroyRate = rate;
    }

    /* Set to be Center Node */
    void setCenter(bool ct)
    {
        this->center = ct;
    }

    /* Check if Center Node */
    bool isCenter()
    {
        return this->center;
    }

    /* Distinguish NodeItem with other QGraphicsItem */
    int type() const;

    /* Return the bounding rect of NodeItem */
    QRectF boundingRect() const;

protected:
    /* Paint BulletItem */
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    /* Process Mouse Press Event in NodeItem */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /* Return the shape path of NodeItem */
    QPainterPath shape();

private:
    qreal x_coordinate;     /* X Coordinate */
    qreal y_coordinate;     /* Y Coordinate */
    qreal z_coordinate;     /* Z Coordinate */
    QHostAddress ipAddr;    /* IP Address */
    bool alive;             /* Mark Alive State */
    EnemyAttr nodeship;     /* Enemy Attribute */
    qreal destroyRate;      /* Destroy Probability of being Attacked */
    bool center;            /* Center Node Mark */
    QString nodeId;             /* Node ID */
};

#endif // NODE_ITEM_H
