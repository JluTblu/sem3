#pragma once

#include <iostream>

class Vector; // предварительное объявление

class Shape
{
protected:
    static int Count; // счётчик объектов
public:
    static Shape* shapes[1000]; // массив указателей на объекты
    Shape();
    virtual ~Shape();

    static void PrintCount();
    static int GetCount();

    virtual void Move(Vector& v) = 0 ;
    virtual void Out() const = 0;
    virtual double Area() const = 0;
};