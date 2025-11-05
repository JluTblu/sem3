#include "MyString.h"
#include <cstring>
#include <iostream>

void MyString::Copy (const char* s)
{
	delete [] m_pStr;
	// Динамически выделяем требуемое количество памяти.
	int len = strlen(s) + 1;
	m_pStr = new char[len];
	// + 1, так как нулевой байт тоже нужно скопировать
	// Если память выделена, копируем строку-аргумент в строку-член класса
	if (m_pStr){
		strncpy (m_pStr, s, len);
		m_pStr[len - 1] = '\0';
	}
}

// Определение конструктора.
MyString::MyString (const char* s)
{
	m_pStr = 0;
	Copy(s);
}

// Определение деструктора.
MyString::~MyString()
{
	// Освобождение памяти, занятой в конструкторе для строки-члена класса
	delete[] m_pStr;
}

// Метод класса
char* MyString::GetString() const
{
	return m_pStr;
}

int MyString::GetLength()
{
	return strlen(m_pStr) + 1;
}

MyString::MyString() : m_pStr(nullptr){}

MyString& MyString::operator= (const MyString &str){
	if (this == &str){
		return *this;
	}
	Copy(str.GetString());
	return *this;
}

MyString::MyString (const MyString &str) : m_pStr(nullptr){
	Copy(str.GetString());
}

std::ostream& operator<<(std::ostream& os, const MyString& ms){
    os << (ms.m_pStr ? ms.m_pStr : "");
    return os;
}




