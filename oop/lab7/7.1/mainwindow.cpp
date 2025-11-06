#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("App");
    resize(600, 450);

    canvas = new Canvas(this);

    QPushButton *btnRect = new QPushButton("Добавить прямоугольник");
    QPushButton *btnEllipse = new QPushButton("Добавить эллипс");
    QPushButton *btnTriangle = new QPushButton("Добавить треугольник");
    QPushButton *btnDelete = new QPushButton("Удалить");

    connect(btnRect, &QPushButton::clicked, canvas, &Canvas::addRectangle);
    connect(btnEllipse, &QPushButton::clicked, canvas, &Canvas::addEllipse);
    connect(btnTriangle, &QPushButton::clicked, canvas, &Canvas::addTriangle);
    connect(btnDelete, &QPushButton::clicked, canvas, &Canvas::deleteActive);

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(btnRect);
    buttons->addWidget(btnEllipse);
    buttons->addWidget(btnTriangle);
    buttons->addWidget(btnDelete);
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addLayout(buttons);
    mainLayout->addWidget(canvas);

    setLayout(mainLayout);
}
