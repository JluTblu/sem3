#pragma once

#include <iostream>

class Vector
{
	double x, y;	// Координаты вектора на плоскости
public:
	//========== Три конструктора
	Vector(double c1 = 0, double c2 = 0);
	~Vector();
	
	//====== Переопределение операций =====//
	Vector& operator= (const Vector& v);	// Присвоение

	Vector (const Vector& v);
	Vector operator+ (const Vector &v);
	double operator! () const;

	bool operator> (const Vector &v) const;
	bool operator< (const Vector &v) const;
	bool operator== (const Vector &v) const;
	Vector operator* (double d) const;
	friend Vector operator* (double d, const Vector &v);
    friend double operator* (const Vector& v1, const Vector& v2); // скалярное произведение (возвращает число!)

	void Out() const;
    double Area() const;
    void Move(Vector& v);

	friend std::ostream& operator<<(std::ostream& os, const Vector& v);

	double getX() const;
	double getY() const;
};

bool bothGreaterThan2(const Vector &v);

