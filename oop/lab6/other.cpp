#include "other.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QScrollBar>
#include <QSpinBox>
#include <QMetaObject>
#include <QSignalSpy>
#include <QtTest>

allMyWidgets::allMyWidgets(QWidget *parent): QWidget(parent), nextY(0){
    
    setMinimumSize(400, 500);
    
    QPushButton *btnAdd = new QPushButton("Добавить виджет", this);// Кнопки управления
    auto *btnConnect = new QPushButton("Соединить все", this);
    auto *btnDelete = new QPushButton("Удаление ласт", this);
    
    btnAdd->setGeometry(10, 10, 180, 30);
    btnConnect->setGeometry(200, 10, 180, 30);
    btnDelete->setGeometry(390, 10, 180, 30);
    
    connect(btnAdd, &QPushButton::clicked, this, &allMyWidgets::addWidget);
    connect(btnConnect, &QPushButton::clicked, this, &allMyWidgets::connectAll);
    connect(btnDelete, &QPushButton::clicked, this, &allMyWidgets::removeLast);
    
    nextY = 50;
}

void allMyWidgets::addWidget(){
    QWidget *newWidget = nullptr;
    
    int type = widgets.size() % 4; // Создаем виджеты циклически
    
    switch (type){
        case 0:{
            auto *label = new QLabel("Значение: 0", this);
            label->setProperty("value", 0);
            newWidget = label;
            break;
        }
        case 1:{
            auto *slider = new QSlider(Qt::Horizontal, this);
            slider->setRange(0, 100);
            slider->setValue(0);
            newWidget = slider;
            break;
        }
        case 2:{
            auto *scrollbar = new QScrollBar(Qt::Horizontal, this);
            scrollbar->setRange(0, 100);
            scrollbar->setValue(0);
            newWidget = scrollbar;
            break;
        }
        case 3:{
            auto *spinbox = new QSpinBox(this);
            spinbox->setRange(0, 100);
            spinbox->setValue(0);
            newWidget = spinbox;
            break;
        }
    }
    
    if (newWidget){
        newWidget->setGeometry(10, nextY, 380, 30);
        newWidget->show();
        widgets.append(newWidget);
        nextY += 40;
    }
}

void allMyWidgets::connectAll(){
    for (int i = 0; i < widgets.size(); ++i){// Соединяем каждый виджет с каждым
        for (int j = i + 1; j < widgets.size(); ++j){
            connectTwoWidgets(widgets[i], widgets[j]);
        }
    }
}

void allMyWidgets::connectTwoWidgets(QWidget *w1, QWidget *w2){
    const char *c1 = w1->metaObject()->className(); // определяется тип каждого виджета
    const char *c2 = w2->metaObject()->className(); // classname вернет имя - типо QSlider или QLabel
    
    const char *signal1 = nullptr, *slot1 = nullptr;// Определяем сигналы и слоты по типу через метаинформацию
    const char *signal2 = nullptr, *slot2 = nullptr;
    
    if (strcmp(c1, "QLabel") == 0){
        slot1 = SLOT(setNum(int)); // QLabel не имеет сигналов изменения, только слот
    } else if (strcmp(c1, "QSlider") == 0){
        signal1 = SIGNAL(valueChanged(int));
        slot1 = SLOT(setValue(int));
    } else if (strcmp(c1, "QScrollBar") == 0){
        signal1 = SIGNAL(valueChanged(int));
        slot1 = SLOT(setValue(int));
    } else if (strcmp(c1, "QSpinBox") == 0){
        signal1 = SIGNAL(valueChanged(int));
        slot1 = SLOT(setValue(int));
    }
    
    if (strcmp(c2, "QLabel") == 0){
        slot2 = SLOT(setNum(int));
    } else if (strcmp(c2, "QSlider") == 0){
        signal2 = SIGNAL(valueChanged(int));
        slot2 = SLOT(setValue(int));
    } else if (strcmp(c2, "QScrollBar") == 0){
        signal2 = SIGNAL(valueChanged(int));
        slot2 = SLOT(setValue(int));
    } else if (strcmp(c2, "QSpinBox") == 0){
        signal2 = SIGNAL(valueChanged(int));
        slot2 = SLOT(setValue(int));
    }
    
    if (signal1 && slot2){
        QObject::connect(w1, signal1, w2, slot2, Qt::UniqueConnection); // UniqueConnection предотвращает повторное соединение
    } // если уже было
    if (signal2 && slot1){
        QObject::connect(w2, signal2, w1, slot1, Qt::UniqueConnection);
    }
}

void allMyWidgets::removeLast(){
    QWidget *last = widgets.last();
    widgets.removeLast();
    last->deleteLater();
}