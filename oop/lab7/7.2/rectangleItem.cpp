#include "rectangleItem.h"
#include "another.h"

rectangleItem::rectangleItem(const QRectF &rect) : QGraphicsRectItem(rect){
    setFlags(ItemIsMovable | ItemIsSelectable);
    setBrush(Qt::blue);
}

void rectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setZValue(++zCounter);
    QGraphicsRectItem::mousePressEvent(event);
}

void rectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsRectItem::mouseMoveEvent(event);
}