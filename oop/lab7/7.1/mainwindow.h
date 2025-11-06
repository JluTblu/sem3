#pragma once

#include <QWidget>
#include "canvas.h"

class MainWindow : public QWidget{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    Canvas *canvas;
};