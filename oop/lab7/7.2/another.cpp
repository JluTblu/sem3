#include "another.h"
#include "rectangleItem.h"
#include "ellipseItem.h"
#include "triangleItem.h"
#include <QRandomGenerator>

int zCounter = 0;

myWidgets::myWidgets(QWidget *parent) : QWidget(parent){
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setSceneRect(0, 0, 800, 600);

    btnAddRect = new QPushButton("Добавить прямоугольник");
    btnAddEllipse = new QPushButton("Добавить эллипс");
    btnAddTriangle = new QPushButton("Добавить треугольник");
    btnDelete = new QPushButton("Удалить");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnAddRect);
    buttonLayout->addWidget(btnAddEllipse);
    buttonLayout->addWidget(btnAddTriangle);
    buttonLayout->addWidget(btnDelete);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(view);
    setLayout(mainLayout);

    connect(btnAddRect, &QPushButton::clicked, this, &myWidgets::addRectangle);
    connect(btnAddEllipse, &QPushButton::clicked, this, &myWidgets::addEllipse);
    connect(btnAddTriangle, &QPushButton::clicked, this, &myWidgets::addTriangle);
    connect(btnDelete, &QPushButton::clicked, this, &myWidgets::deleteSelected);
}

myWidgets::~myWidgets(){}

void myWidgets::mousePressEvent(QMouseEvent *event){ // добавил
    lastClickPos = view->mapToScene(event->pos());
}

void myWidgets::addRectangle(){
    rectangleItem *item = new rectangleItem(QRectF(lastClickPos.x() - 50, lastClickPos.y() - 30, 100, 60));
    item->setZValue(++zCounter);
    scene->addItem(item);
    addedItems.append(item);
}

void myWidgets::addEllipse(){
    auto *item = new ellipseItem(QRectF(lastClickPos.x() - 60, lastClickPos.y() - 30, 120, 60));
    item->setZValue(++zCounter);
    scene->addItem(item);
    addedItems.append(item);
}

void myWidgets::addTriangle(){
    QPolygonF triangle;
    // triangle << QPointF(0, 60) << QPointF(50, 0) << QPointF(100, 60);
    triangle << QPointF(lastClickPos.x() - 50, lastClickPos.y() + 30) << QPointF(lastClickPos.x(), lastClickPos.y() - 30) << QPointF(lastClickPos.x() + 50, lastClickPos.y() + 30); //правый угол
    triangleItem *item = new triangleItem(triangle);
    item->setZValue(++zCounter);
    scene->addItem(item);
    addedItems.append(item);
}

void myWidgets::deleteSelected(){
    QList<QGraphicsItem*> selected = scene->selectedItems();

    if (!selected.isEmpty()){
        for (auto *item : selected){
            scene->removeItem(item);
            addedItems.removeOne(item);
            delete item;
        }
    } else if (!addedItems.isEmpty()){
        QGraphicsItem* last = addedItems.last();
        scene->removeItem(last);
        delete last;
        addedItems.removeLast();
    }
}

