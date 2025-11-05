#pragma once
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class triangleItem : public QGraphicsPolygonItem{
public:
    triangleItem(const QPolygonF& polygon);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};