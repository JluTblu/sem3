#include "Shape.h"
#include "MyVector.h"
#include <iostream>

using namespace std;

int Shape::Count = 0;
Shape* Shape::shapes[1000] = {nullptr};

Shape::Shape(){
    if (Count < 1000) shapes[Count] = this; // сохраняем указатель на созданный объект
    Count++;
}

Shape::~Shape(){
    Count--;
}

void Shape::PrintCount(){
    cout << "Now there are " << Count << " shapes\n";
}

int Shape::GetCount(){
    return Count;
}
