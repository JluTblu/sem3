#pragma once
#include "Shape.h"

class Vector : public Shape 
{
	double x, y;	// Координаты вектора на плоскости
	// static int Count;
public:
	static void PrintCount();
	//========== Три конструктора
	Vector(double c1, double c2);
	Vector();							// Default
	~Vector();
	
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение

	Vector (const Vector& v);
	Vector operator+ (const Vector &v);
	double operator! () const;

	bool operator> (const Vector &v) const;
	bool operator== (const Vector &v) const;
	Vector operator* (double d) const;
	friend Vector operator* (double d, const Vector &v);
    friend double operator* (const Vector& v1, const Vector& v2); // скалярное произведение (возвращает число!)

	void Out() const override;
    double Area() const override;
    void Move(Vector& v) override;

	friend class Rect;
    friend class Circle;
};

