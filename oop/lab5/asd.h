#pragma once

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class HelloWidget : public QWidget{
public:
    HelloWidget(QWidget *parent = nullptr) : QWidget(parent){
        setWindowTitle("App");
        resize(300, 150);

        QLabel *label = new QLabel("Hello World", this);
        label->setGeometry(120, 20, 100, 30); // x, y, width, height

        QPushButton *exitButton = new QPushButton("Exit", this);
        exitButton->setGeometry(100, 70, 100, 30);

        connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    }
};