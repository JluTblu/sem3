#include "Shape.h"
#include "MyVector.h"
#include "Rect.h"
#include <cmath>
#include <cfloat>
#include <iostream>


using namespace std;

Rect::Rect() : ptLT(0, 0), ptRB(0, 0){}

Rect::Rect(const Vector& LT, const Vector& RB) : ptLT(LT), ptRB(RB){}

Rect::Rect(double left, double top, double right, double bottom) : ptLT(left, top), ptRB(right, bottom){}

Rect::Rect(const Rect& other) : ptLT(other.ptLT), ptRB(other.ptRB){}

Rect& Rect::operator= (const Rect& other){
    if (this == &other) return *this;
    ptLT = other.ptLT;
    ptRB = other.ptRB;
    return *this;
}

double Rect::Width() const{
    return ptRB.x - ptLT.x;
}

double Rect::Height() const{
    return ptRB.y - ptLT.y;
}

void Rect::Inflate(double factor){
    ptLT.x -= factor; ptLT.y -= factor; ptRB.x += factor; ptRB.y += factor;
}

void Rect::Inflate(double dx, double dy){
    ptLT.x -= dx;
    ptLT.y -= dy;
    ptRB.x += dx;
    ptRB.y += dy;
}

void Rect::Inflate(double left, double top, double right, double bottom){
    ptLT.x -= left; // левая — влево
    ptLT.y -= top; // верхняя — вверх
    ptRB.x += right; // правая — вправо
    ptRB.y += bottom; // нижняя — вниз
}

void Rect::Move(Vector& v){
    ptLT = ptLT + v;
    ptRB = ptRB + v;
}

void Rect::Out() const{
    cout << "\"Rect (" << ptLT.x << "," << ptLT.y << "," << ptRB.x << "," << ptRB.y << ")\"" << endl;
}

double Rect::Area() const{
    return (ptRB.x - ptLT.x) * (ptRB.y - ptLT.y);
}
















