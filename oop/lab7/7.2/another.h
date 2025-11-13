#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

extern int zCounter;

class myWidgets : public QWidget{
    Q_OBJECT
   
public:
    myWidgets(QWidget *parent = nullptr);
    ~myWidgets();

public slots:
    void addRectangle();
    void addEllipse();
    void addTriangle();
    void deleteSelected();

private:
    QList<QGraphicsItem*> addedItems;
    QPointF lastClickPos; // x, y

    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *btnAddRect;
    QPushButton *btnAddEllipse;
    QPushButton *btnAddTriangle;
    QPushButton *btnDelete;
protected:
    void mousePressEvent(QMouseEvent *event);
};
