#include "figure.h"

Figure::Figure(Type type, const QRect &rect, const QColor &color) : type(type), rect(rect), color(color){}

void Figure::draw(QPainter *painter) const{
    painter->setBrush(color);

    switch (type){
    case Rectangle:
        painter->drawRect(rect);
        break;
    case Ellipse:
        painter->drawEllipse(rect);
        break;
    case Triangle:{
        QPolygon triangle;
        QPoint top(rect.center().x(), rect.top());
        QPoint left(rect.left(), rect.bottom());
        QPoint right(rect.right(), rect.bottom());
        triangle << top << left << right;
        painter->drawPolygon(triangle);
        break;
    }
    }
}

bool Figure::contains(const QPoint &p) const{
    if (type == Triangle){
        QPolygon triangle;
        QPoint top(rect.center().x(), rect.top());
        QPoint left(rect.left(), rect.bottom());
        QPoint right(rect.right(), rect.bottom());
        triangle << top << left << right;
        return triangle.containsPoint(p, Qt::OddEvenFill);
    }
    return rect.contains(p);
}

