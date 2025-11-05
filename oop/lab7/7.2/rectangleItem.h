#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class rectangleItem : public QGraphicsRectItem{
public:
    rectangleItem(const QRectF& rect);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};