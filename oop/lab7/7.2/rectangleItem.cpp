#include "rectangleItem.h"

rectangleItem::rectangleItem(const QRectF &rect) : QGraphicsRectItem(rect){
    setFlags(ItemIsMovable | ItemIsSelectable);
    setBrush(Qt::blue);
}

void rectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setZValue(zValue() + 1);
    QGraphicsRectItem::mousePressEvent(event);
}

void rectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsRectItem::mouseMoveEvent(event);
}