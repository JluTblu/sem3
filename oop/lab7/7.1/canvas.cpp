#include "canvas.h"
#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent) : QWidget(parent){
    setMinimumSize(500, 400);
}

void Canvas::addRectangle(){
    Figure *f = new Figure(Figure::Rectangle, QRect(50, 50, 120, 80), QColor("lightblue"));
    figures.append(f);
    update();
}

void Canvas::addEllipse(){
    auto *f = new Figure(Figure::Ellipse, QRect(150, 100, 100, 100), QColor("lightgreen"));
    figures.append(f);
    update();
}

void Canvas::addTriangle(){
    auto *f = new Figure(Figure::Triangle, QRect(250, 80, 100, 100), QColor("red"));
    figures.append(f);
    update();
}

void Canvas::deleteActive(){
    if (active){
        figures.removeOne(active);
        delete active;
        active = nullptr;
    } else if (!figures.isEmpty()){
        Figure *last = figures.takeLast(); // удаляет из списка и возвращает
        delete last;
    }
    update();
}

void Canvas::paintEvent(QPaintEvent *){
    QPainter p(this); // рисуем именно на текущем виджете
    for (Figure *f : figures)
        f->draw(&p);
    // if (active){
    //     p.setPen(Qt::red);
    //     p.drawRect(active->getRect());
    // }
}

void Canvas::mousePressEvent(QMouseEvent *event){
    for (int i = figures.size() - 1; i >= 0; --i){
        Figure *f = figures[i];
        if (f->contains(event->pos())){ // попали ли курсором по фигуре
            active = f;
            dragOffset = event->pos() - f->getRect().topLeft(); // сохраняем смещение относительно угла фигуры
            figures.removeAt(i); // поднимаем активную фигуру наверх
            figures.append(f); // сначала удаляя ее из списка, а после добавляя в конец
            update();
            return;
        }
    }
    active = nullptr;
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    if (active && (event->buttons() & Qt::LeftButton)){
        QRect r = active->getRect();
        r.moveTopLeft(event->pos() - dragOffset); //это новый верхний левый угол фигуры, чтобы фигура двигалась плавно
        active->getRect() = r;
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *){
    dragOffset = QPoint(); // сбрасываем в ноль, не перетаскиваем ничего
}
