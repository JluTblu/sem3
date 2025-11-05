#pragma once

#include <iostream>

using namespace std;

class Point{

private:
    double x;
    double y;
public:
    Point(double x_, double y_);
    Point();
    Point(const Point& other);

    double getX() const;
    double getY() const;

    void setX(double value);
    void setY(double value);
    void set(double valueX, double valueY);

    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    bool operator<(const Point& other) const;
};

void toLowerCase(string& str);
