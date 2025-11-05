#pragma once

#include <QWidget>
#include <QList>

class allMyWidgets : public QWidget {
    Q_OBJECT

private:
    QList<QWidget*> widgets;
    int nextY;
    
    void connectTwoWidgets(QWidget *w1, QWidget *w2);
    
public:
    explicit allMyWidgets(QWidget *parent = nullptr);
    
public slots:
    void addWidget();
    void connectAll();
    void removeLast();
};