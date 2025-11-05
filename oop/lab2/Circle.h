#pragma once

#include "Shape.h"
#include "MyVector.h"
#include <cmath>

class Circle : public Shape
{
    Vector ptCntr;
    double R;
public:
    Circle(double x, double y, double radius);

    virtual void Move(Vector& v) override;
    virtual void Out() const override;
    virtual double Area() const override;
};
