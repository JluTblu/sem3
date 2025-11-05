class MyString
{
private:
	char* m_pStr;		// Элемент данных класса (адрес строки)
public:
    MyString ();
	MyString (const char* s);	// Объявление конструктора
    ~MyString();		// Объявление деструктора

	void Copy (const char* s);
	const char* GetString() const;	// Объявление метода (accessor)
	int GetLength() const;	// Объявление метода (длина строки)
	MyString (const MyString &str);
	MyString& operator= (const char* str);
	MyString& operator= (const MyString &str);
};
