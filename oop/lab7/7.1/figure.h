#pragma once

#include <QRect>
#include <QColor>
#include <QPainter>

class Figure{
public:
    enum Type { Rectangle, Ellipse, Triangle };
private:
    Type type;
    QRect rect;
    QColor color;
public:
    Figure(Type type, const QRect &rect, const QColor &color);

    void draw(QPainter *painter) const;
    bool contains(const QPoint &p) const;

    Type getType() const{ 
        return type;
    }
    QRect &getRect(){
        return rect;
    }
    const QRect &getRect() const{
        return rect;
    }
};