#include "ellipseItem.h"

ellipseItem::ellipseItem(const QRectF &rect) : QGraphicsEllipseItem(rect){
    setFlags(ItemIsMovable | ItemIsSelectable);
    setBrush(Qt::green);
}

void ellipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setZValue(zValue() + 1);
    QGraphicsEllipseItem::mousePressEvent(event);
}

void ellipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsEllipseItem::mouseMoveEvent(event);
}