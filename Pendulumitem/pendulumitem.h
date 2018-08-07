#ifndef PENDULUMITEM_H
#define PENDULUMITEM_H
#include <QGraphicsItem>
#include <QTimeLine>

class Pendulumitem : public QGraphicsItem
{
public:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // PENDULUMITEM_H
