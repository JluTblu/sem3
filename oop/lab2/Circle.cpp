#include "Shape.h"
#include "MyVector.h"
#include "Circle.h"
#include <iostream>
#include <cmath>
    
using namespace std;

Circle::Circle(double x, double y, double radius) : ptCntr(x,y), R(radius){}

void Circle::Move(Vector& v){
    ptCntr = ptCntr + v;
}

void Circle::Out() const{
    cout << "Circle: center=(" << ptCntr.x << "," << ptCntr.y
                  << ") R=" << R << "\n";
}

double Circle::Area() const{
    return M_PI * R * R;
}