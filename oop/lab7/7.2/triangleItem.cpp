#include "triangleItem.h"
#include "another.h"

triangleItem::triangleItem(const QPolygonF &polygon) : QGraphicsPolygonItem(polygon){
    setFlags(ItemIsMovable | ItemIsSelectable);
    setBrush(Qt::red);
}

void triangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setZValue(++zCounter);
    QGraphicsPolygonItem::mousePressEvent(event);
}

void triangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsPolygonItem::mouseMoveEvent(event);
}