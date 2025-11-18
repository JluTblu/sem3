#pragma once

#include <QWidget>
#include <QList>
#include "figure.h"

class Canvas : public QWidget{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr); // конструктор самостоятельный виджет

public slots:
    void addRectangle();
    void addEllipse();
    void addTriangle();
    void deleteActive();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QList<Figure*> figures;
    Figure *active = nullptr;
    QPoint dragOffset;
};
