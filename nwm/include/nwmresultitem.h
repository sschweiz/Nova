#ifndef NWMRESULTITEM_H
#define NWMRESULTITEM_H

#include <QtGui/QColor>
#include <QGraphicsItem>

class nwmResultItem : public QGraphicsItem
{
public:
    nwmResultItem();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
    int x, y;
};

#endif // NWMRESULTITEM_H
