#include <QtGui>
#include "nwmresultitem.h"

nwmResultItem::nwmResultItem()
{
    color.setRgb(80, 80, 80);

    setFlags(ItemIsSelectable);// | ItemIsMovable);
    setAcceptsHoverEvents(true);
}

QRectF nwmResultItem::boundingRect() const
{
    return QRectF(0, 0, 110, 90);
}

QPainterPath nwmResultItem::shape() const
{
    QPainterPath path;
    path.addRect(1, 1, 108, 88);
    return path;
}

void nwmResultItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver) {
        fillColor = fillColor.light(125);
    }

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.125) {
        painter->fillRect(QRectF(0, 0, 110, 90), fillColor);
        return;
    }

    QBrush b = painter->brush();
    painter->setBrush(fillColor);
    painter->drawRoundRect(1, 1, 110, 90, 12, 12);
    painter->setBrush(b);
}

void nwmResultItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void nwmResultItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void nwmResultItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
