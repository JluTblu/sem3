#include "stdafx.h"
#include "Shape.h"
#include "MyVector.h"
#include <cmath>
#include <cfloat>

Vector::Vector (double c1, double c2){
	x=c1;   y=c2;
}

Vector::Vector (){
	x = y = 0.;
}

Vector::~Vector(){
    cout << "Vector destroyed\n";
}

void Vector::Out() const{
	cout << "\nVector:  x = " << x << ",  y = " << y;
}

double Vector::Area() const{
    return 0.0; // площадь точки = 0
}

//====== Переопределение операций =====//
Vector& Vector::operator= (const Vector &v)	// Присвоение
{
	if (this == &v) // случай самоприсваивания, возвращаем текущий по указателю
		return *this;
	x = v.x;
	y = v.y;
	return *this;
}

Vector::Vector(const Vector &v) : x(0), y (0){
	*this = v;
}

Vector Vector::operator+ (const Vector &v){
	return Vector(x + v.x, y + v.y);
}

double Vector::operator! () const{
	return std::sqrt(x * x + y * y);
}

bool Vector::operator> (const Vector &v) const{
	return (!(*this)) > (!v);
}

bool Vector::operator== (const Vector &v) const{
    return (std::fabs(x - v.x) < DBL_EPSILON) && (std::fabs(y - v.y) < DBL_EPSILON);
}

Vector Vector::operator* (double d) const{
	return Vector(x * d, y * d);
}

Vector operator* (double d, const Vector &v){
	return Vector(v.x * d, v.y * d);
}

double operator* (const Vector &v1, const Vector &v2){
	return v1.x * v2.x + v1.y * v2.y;
}

void Vector::PrintCount(){
	cout << "\n Now there are " << Count << " vectors";
}

void Vector::Move(Vector& v){
    x += v.x;
    y += v.y;
}