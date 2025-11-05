#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
    
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *btnAddRect;
    QPushButton *btnAddEllipse;
    QPushButton *btnAddTriangle;
    QPushButton *btnDelete;
    int zCounter = 0;
};