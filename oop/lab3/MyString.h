#include <iostream>

class MyString
{
private:
	char* m_pStr;// (адрес строки)
public:
    MyString ();
	MyString (const char* s); //конструктор
    ~MyString();//деструктор

	void Copy (const char* s);
	char* GetString() const;
	int GetLength();
	MyString (const MyString &str);
	MyString& operator= (const MyString &str);

	friend std::ostream& operator<<(std::ostream& os, const MyString& ms);

};
