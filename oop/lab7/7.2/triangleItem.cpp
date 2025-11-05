#include "triangleItem.h"

triangleItem::triangleItem(const QPolygonF &polygon) : QGraphicsPolygonItem(polygon){
    setFlags(ItemIsMovable | ItemIsSelectable);
    setBrush(Qt::red);
}

void triangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setZValue(zValue() + 1);
    QGraphicsPolygonItem::mousePressEvent(event);
}

void triangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsPolygonItem::mouseMoveEvent(event);
}