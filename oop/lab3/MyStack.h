#pragma once

#include <iostream>

// Исключения
struct StackOverflow{
    void Out() const { std::cout << "\nОшибка: переполнение стека!"; }
};

struct StackUnderflow{
    void Out() const{ std::cout << "\nОшибка: стек пуст!"; }
};

struct StackOutOfRange{
    int index;
    StackOutOfRange(int idx) : index(idx){}
    void Out() const { std::cout << "\nОшибка: выход за пределы индекса!" << "index: " << this->index; }
};

template <class T, size_t N>
class MyStack{

    T arr[N];
    size_t size;

    public:

    MyStack() : size(0){}

    void Push(const T& value){
        if(size >= N) throw StackOverflow();
        arr[size++] = value;
    }

    T Pop(){
        if(size == 0) throw StackUnderflow();
        return arr[size--];
    }
    size_t GetSize() const{ return size; }
    size_t Capacity() const{ return N; }

    T& operator[](size_t index){
        if(index >= size) throw StackOutOfRange(index);
        return arr[index];
    }


};