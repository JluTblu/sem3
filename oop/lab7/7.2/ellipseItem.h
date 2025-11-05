#pragma once
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class ellipseItem : public QGraphicsEllipseItem{
public:
    ellipseItem(const QRectF& rect);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};