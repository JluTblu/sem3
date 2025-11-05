#include "stdafx.h"
#include "MyString.h"

void MyString::Copy(const char* s){
    delete[] m_pStr;
    if (!s){ // проверка на nullptr
        m_pStr = nullptr;
        return;
    }
    int len = strlen(s) + 1;
    m_pStr = new char[len];
    strcpy(m_pStr, s);
}

// Определение конструктора.
MyString::MyString(const char* s) : m_pStr(nullptr) {
    Copy(s);
}


// Определение деструктора.
MyString::~MyString()
{
	// Освобождение памяти, занятой в конструкторе для строки-члена класса
	delete[] m_pStr;
}

// Метод класса
const char* MyString::GetString() const {
    return m_pStr ? m_pStr : "";
}

int MyString::GetLength() const{
    return m_pStr ? strlen(m_pStr) : 0;
}


MyString::MyString() : m_pStr(nullptr){}

MyString& MyString::operator= (const MyString &str){
	if (this == &str){
		return *this;
	}
	Copy(str.GetString());
	return *this;
}

MyString& MyString::operator= (const char* str){
    if (str == nullptr) {
        delete[] m_pStr;
        m_pStr = nullptr;
        return *this;
    }
    Copy(str);
    return *this;
}

MyString::MyString (const MyString &str) : m_pStr(nullptr){
	Copy(str.GetString());
}




