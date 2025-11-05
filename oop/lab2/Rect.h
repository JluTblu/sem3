#pragma once
#include "Shape.h"
#include "MyVector.h"

class Rect : public Shape
{
private:
    Vector ptLT;
	Vector ptRB;
public:
    Rect (); // по умолчанию
    Rect (const Vector& LT, const Vector& RB); // от двух векторов
    Rect (double left, double top, double right, double bottom); // от координат

    Rect (const Rect& other);
    Rect& operator= (const Rect& other);

    double Width() const;
    double Height() const;

    // void Out() const;

    void Inflate(double factor = 1.0);
    void Inflate(double dx, double dy);
    void Inflate(double left, double top, double right, double bottom);

    void Move(Vector& v) override;
    void Out() const override;
    double Area() const override;
};