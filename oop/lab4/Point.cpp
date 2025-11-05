#include "Point.h"

using namespace std;

Point::Point(double x_, double y_){
    x = x_;
    y = y_;
}
Point::Point() : x(0), y(0){}
Point::Point(const Point& other) : x(other.x), y(other.y){}

double Point::getX() const{
    return x;
}
double Point::getY() const{
    return y;
}

void Point::setX(double value){
    x = value;
}
void Point::setY(double value){
    y = value;
}
void Point::set(double valueX, double valueY){
    x = valueX;
    y = valueY;
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

bool Point::operator<(const Point& other) const{
    if (x != other.x) return x < other.x; // Сначала сравниваем x
    return y < other.y; // При равенстве x сравниваем y
}

void toLowerCase(string& str){
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){
        return tolower(c);
    });
}
