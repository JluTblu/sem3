//=======================================================================
//	Лабораторная №3. Шаблоны функций. Шаблоны классов. Стандартные шаблоны С++.
//				Обработка исключений.
//=======================================================================
//Используйте недостающие файлы из лабораторной 2

#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include "MyVector.h"
#include "MyString.h"
#include "MyStack.h"
#include "Other.h"
#include "Compare.h"

using namespace std;

//============= Шаблон функции для вывода с помощью итератора
template <class T> void pr(T& v, string s)
{
	cout<<"\n\n\t"<<s<<"  # Sequence:\n";
	
	// Итератор любого контейнера
	typename T::iterator p;
	int i;

	for (p = v.begin(), i=0;  p != v.end();  p++, i++)
		cout << endl << i+1 <<". "<< *p;
	cout << '\n';
}

int main()
{

	//===========================================================
	// Шаблоны функций
	//===========================================================
	// Создайте шаблон функции перестановки двух параметров - Swap().
	// Проверьте работоспособность созданного шаблона с помощью
	// приведенного ниже фрагмента.
	{
		int i = 1, j = -1;
		Swap (i, j);

		double a = 0.5, b = -5.5;
		Swap (a, b);

		Vector u(1,2), w(-3,-4);
		Swap(u, w);

		// Если вы достаточно развили класс MyString в предыдущей работе,
		// то следующий фрагмент тоже должен работать корректно.
		
		MyString s1 ("Your fault"), s2 ("My forgiveness");
		Swap (s1, s2);
	}
	//===========================================================
	// Шаблоны классов
	//===========================================================
	// Создайте шаблон класса MyStack для хранения элементов любого типа T.
	// В качестве основы для стека может быть выбран массив.
	// Для задания максимального размера стека может быть использован
	// параметр-константа шаблона
	// Обязательными операциями со стеком являются "Push" и "Pop","GetSize" и "Capacity"
	// Необязательной - может быть выбор по индексу (operator[]).
	// Для того, чтобы гарантировать корректное выполнение этих операций 
	// следует генерировать исключительные ситуации.
	
	// С помощью шаблона MyStack создайте стек переменных типа int, затем
	// стек переменных типа double и, наконец, стек из переменных типа Vector 
	// Если вы подготовите три класса для обработки исключений,
	// то следующий фрагмент должен работать
	try
	{
		cout << "\tTest MyStack\n";
		MyStack <int, 3> stack;

		cout << "\nInteger Stack capacity: " << stack.Capacity();

		stack.Push(1);
		stack.Push(2);
		stack.Push(3);
		
		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";

		// stack.Push(4); // Здесь должно быть "выброшено" исключение StackOverflow

		cout << "\nInteger Stack pops: " << stack.Pop();
		cout << "\nInteger Stack pops: " << stack.Pop();
		
		cout << "\nInteger Stack has: " << stack.GetSize() << " elements";
		stack.Pop();
		// stack.Pop(); // Здесь должно быть "выброшено" исключение StackUnderflow
		stack.Push(2);
		
		int i = stack[3]; // Здесь должно быть "выброшено" исключение StackOutofRange
		
		MyStack<Vector, 5> ptStack;
		
		cout << "\nVector Stack capacity: " << ptStack.Capacity();
		
		ptStack.Push(Vector(1,1));
		ptStack.Push(Vector(2,2));
		
		cout << "\nVector Stack pops: ";
		// Используйте метод класса Vector для вывода элемента
		ptStack.Pop().Out();
		
		cout << "\nVector Stack has: " << ptStack.GetSize() << " elements";
	}
	catch (StackOverflow)
	{
		cout << "\nStack overflow";
	}
	catch (StackUnderflow)
	{
		cout << "\nStack underflow";
	}
	catch (const StackOutOfRange &iskl)
	{
		iskl.Out(); 
	}

	//=======================================================================
	// Контейнеры стандартной библиотеки. Последовательности типа vector
	//=======================================================================
	
	// Создайте пустой вектор целых чисел. Узнайте его размер с помощью метода size(),
	// С помощью метода push_back() заполните вектор какими-либо значениями.
	// Получите новый размер вектора и выведите значения его элементов.
	// В процессе работы с вектором вы можете кроме количества реально заполненных
	// элементов (size()) узнать максимально возможное количество элементов (max_size()),
	// а также зарезервированную память (capacity()).

	vector<int> v;
	int n = v.size();
	v.push_back(-1);
	v.push_back(-2);
	n = v.size();
	cout << "size: " << n << " capacity: " << v.capacity() << " max_size: " << v.max_size() << endl;
		
	// Так как мы часто будем выводить последовательности, то целесообразно
	// создать шаблон функции для вывода любого контейнера.
	// Проанализируйте коды такого шабдлона (pr), который приведен выше
	// Используйте его для вывода вашего вектора

	pr (v, "Vector of ints");
	
	// Используем другой конструктор для создания вектора вещественных
	// с начальным размером в 2 элемента и заполнением (222.).
	// Проверим параметры вектора. Затем изменим размер вектора и его заполнение
	// (метод - resize()) и вновь проверим параметры.
	
	// Вектор вещественных с начальным размером 2 и заполнением 222.

	vector<double> vd(2, 222.);
	pr(vd, "Vector of doubles");
	cout << "size: " << vd.size() << " capacity: " << vd.capacity() << " max_size: " << vd.max_size() << endl;

	vd.resize(5, 333.); // Меняем размер и заполняем другим значением
	pr (vd, "After resize");
	cout << "size: " << vd.size() << " capacity: " << vd.capacity() << " max_size: " << vd.max_size() << endl;

	// Используя метод at(), а также операцию выбора [], измените значения
	// некоторых элементов вектора и проверьте результат.

	vd.at(0) = 52.;
	vd[1] = 812.;
	pr (vd, "After at");
	
	// Создайте вектор вещественных, который является копией существующего.

	vector<double> wd(vd);
	pr (wd, "Copy");
	
	// Создайте вектор, который копирует часть существующей последовательности

	vector<double> ud(vd.begin() + 1, vd.begin() + 4);
	pr (ud, "Copy part");
	for(auto &v : ud){
    	cout << v << " ";
	} cout << endl;

	// Создайте вектор вещественных, который является копией части обычного массива.

	double ar[] = { 0., 1., 2., 3., 4., 5. };
	vector<double> va(ar + 1, ar + 5); // копируем элементы 1..4
	pr (va, "Copy part of array");
	
	// Создайте вектор символов, который является копией части обычной строки

	char s[] = "Array is a succession of chars";
	vector<char> vc(s, s + 5); // только первые 5 символов
	pr (vc, "Copy part of string");

	// Создайте вектор элементов типа Vector и инициализируйте
	// его вектором с координатами (1,1).

	vector<Vector> vv(3, Vector(1, 1));
	
	cout << "\n\nvector of Vectors\n";
	for (int i=0;  i < vv.size();  i++)
		vv[i].Out();

	// Создайте вектор указателей на Vector и инициализируйте его адресами
	// объектов класса Vector
	
	Vector a(1, 2), b(3, 4), c(5, 6);
	vector<Vector*> vp = { &a, &b, &c }; 
	
	cout << "\n\nvector of pointers to Vector\n";
	
	for (size_t i=0;  i < vp.size();  i++)
		vp[i]->Out();

	// Научитесь пользоваться методом assign и операцией
	// присваивания = для контейнеров типа vector.

	vp.assign({ &c, &a, &b });
	cout << "\n\nAfter assign\n";
	for (size_t i=0;  i < vp.size();  i++)
		vp[i]->Out();
	
	// Декларируйте новый вектор указателей на Vector и инициализируйте его 
	// с помощью второй версии assign

	vector<Vector*> vpNew;
	vpNew.assign(vp.begin(), vp.end());
	
	cout << "\n\nNew vector after assign\n";
	for (size_t i=0;  i < vpNew.size();  i++)
		vpNew[i]->Out();

	// На базе шаблона vector создание двухмерный массив и
	// заполните его значениями разными способами.
	// Первый вариант - прямоугольная матрица
	// Второй вариант - ступенчатая матрица

	vector<vector<double>> rect(3, vector<double>(4, 1.5));
	for (size_t i=0; i < rect.size(); i++)
	{
		cout << endl;
		for (size_t j=0; j < rect[i].size(); j++)
			cout << rect[i][j] << "  ";
	}

	//========= Ступенчатая матрица

	vector<vector<double>> vdd(5);
	for (size_t i=0; i < vdd.size(); i++)
		vdd[i] = vector<double>(i+1, double(i));
	
	cout << "\n\n\tTest vector of vector<double>\n";
	for (size_t i=0; i < vdd.size(); i++)
	{
		cout << endl;
		for (size_t j=0; j < vdd[i].size(); j++)
			cout << vdd[i][j] << "  ";
	}

	//===================================
	// Простейшие действия с контейнерами
	//===================================
	//3б. Получение значения первого и последнего элементов последовательности.
	//Получение размера последовательности. Присваивание значений
	//элементов одной последовательности элементам другой - assign().

	//Создайте и проинициализируйте вектор из элементов char. Размер -
	//по желанию.

	vector<char> vChar1 = { 'A','B','C','D','E' };

	//Создайте и проинициализируйте массив из элементов char. Размер -
	//по желанию.

	char cMas[] = { 'X','Y','Z','Q','W' };

	//Получите значение первого элемента вектора ( front() )
	//Получите значение последнего элемента вектора ( back() )
	//Получите размер вектора

	cout << "\nfront: " << vChar1.front() << " back: " << vChar1.back() << " size: " << vChar1.size() << endl;

	//Присвойте вектору любой диапазон из значений массива cMas.
	//Проверьте размер вектора, первый и последний элементы.

	vChar1.assign(cMas, cMas + 5);
	cout << "after assign size: " << vChar1.size() << " front: " << vChar1.front() << " back: " << vChar1.back() << endl;

	//3в. Доступ к произвольным элементам вектора с проверкой - at()
	//и без проверки - []
	//Создайте неинициализированный вектор из 8 элементов char - vChar2.
	//С помощью at() присвойте четным элементам вектора значения
	//элементов vChar1 из предыдущего задания,
	//а с помощью [] присвойте нечетным элементам вектора vChar2 значения
	//массива {'K','U','K','U'}.

	vector<char> vChar2(8);
	for (int i = 0; i < vChar2.size(); i++){
    	if(i % 2 == 0) vChar2.at(i) = vChar1[i % vChar1.size()];
    	else vChar2[i] = "KUKU"[i % 4];
	}
	pr(vChar2, "Задание 3в");

	//Попробуйте "выйти" за границы вектора с помощью at() и
	//с помощью []. Обратите внимание: что происходит при
	//попытке обращения к несуществующему элементу в обоих случаях

	// cout << vChar2[100] = '!'; << endl;

	try{
	cout << vChar2.at(9) << endl;	
	}
	catch(std::out_of_range){

	}
	//3г.Добавьте в конец вектора vChar2  - букву Z (push_back()). Для
	//расширения кругозора можете ее сразу же и выкинуть (pop_back())

	vChar2.push_back('Z');
	vChar2.pop_back();

	//3д. Вставка-удаление элемента последовательности insert() - erase()
	//Очистка последовательности - clear()

	//Вставьте перед каждым элементом вектора vChar2 букву 'W'
	
	for(int i = 0; i < vChar2.size(); i += 2){
    	vChar2.insert(vChar2.begin() + i, 'W');
	}

	//Вставьте перед 5-ым элементом вектора vChar2 3 буквы 'X'

	vChar2.insert(vChar2.begin() + 4, 'X');
	vChar2.insert(vChar2.begin() + 4, 'X');
	vChar2.insert(vChar2.begin() + 4, 'X');
	for(size_t i = 0; i < vChar2.size(); i++){
		cout << vChar2[i] << " ";
	} cout << endl;

	//Вставьте перед 2-ым элементом вектора vChar2 с третьего по
	//шестой элементы массива "aaabbbccc"

	char arr[] = "aaabbbccc";
	vChar2.insert(vChar2.begin() + 1, arr + 2, arr + 6);
  
	//Сотрите c первого по десятый элементы vChar2

    vChar2.erase(vChar2.begin(), vChar2.begin() + 10);
	
	//Уничтожьте все элементы последовательности - clear()

	vChar2.clear();

	//Создание двухмерного массива

///////////////////////////////////////////////////////////////////

	//Задание 4. Списки. Операции, характерные для списков.
	//Создайте два пустых списка из элементов Vector - ptList1 и
	//ptList2

	list<Vector> ptList1, ptList2;

	//Наполните оба списка значениями с помощью методов push_back(),
	//push_front, insert()

	ptList1.push_back(Vector(1, 1));
	ptList1.push_back(Vector(9, 9));
	ptList1.push_front(Vector(3, 4));
	ptList2.push_back(Vector(0, 8));
	ptList2.insert(ptList2.begin(), Vector(0, 0));

	//Отсортируйте списки - sort().
	//Подсказка: для того, чтобы работала сортировка, в классе Vector
	//должен быть переопределен оператор "<"

	ptList1.sort();
	ptList2.sort();
	cout << "ptList1: ";
	for(auto &v : ptList1){
    	v.Out();
    	cout << " ";
	}
	cout << "\n\nptList2: ";
	for(auto &v : ptList2){
    	v.Out();
    	cout << " ";
	}

	//Объедините отсортированные списки - merge(). Посмотрите: что
	//при этом происходит со вторым списком.

	ptList1.merge(ptList2); // ptList2 станет пустым
	cout << "\n\nptList1 after merge: ";
	for(auto &v : ptList1){
    	v.Out();
    	cout << " ";
	}
	cout << "\n\nptList2 after merge: ";
	for(auto &v : ptList2){
    	v.Out();
    	cout << " ";
	}

	//Исключение элемента из списка - remove()
	//Исключите из списка элемент с определенным значением.
	//Подсказка: для этого необходимо также переопределить
	//в классе Vector оператор "=="

	ptList1.remove(Vector(1, 2));

///////////////////////////////////////////////////////////////////

	//Задание 5. Стандартные алгоритмы.Подключите заголовочный файл
	// <algorithm>
	//5а. Выведите на экран элементы ptList1 из предыдущего
	//задания с помощью алгоритма for_each()

	for_each(ptList1.begin(), ptList1.end(), [](const Vector& v){
		v.Out();
	});

	//5б.С помощью алгоритма find() найдите итератор на элемент Vector с
	//определенным значением. С помощью алгоритма find_if() найдите
	//итератор на элемент, удовлетворяющий определенному условию, 
	//например, обе координаты точки должны быть больше 2.
	//Подсказка: напишите функцию-предикат, которая проверяет условие
	//и возвращает boolean-значение (предикат может быть как глобальной
	//функцией, так и методом класса)

	auto it = find(ptList1.begin(), ptList1.end(), Vector(0, 0)); // find
	if (it != ptList1.end()){
		cout << "\n\nFound (0,0)";
	}

	auto it2 = find_if(ptList1.begin(), ptList1.end(), [](const Vector& v){ // find_if
		return bothGreaterThan2(v);
	});

	if(it2 != ptList1.end()){
    	cout << "\nПервый элемент, где обе координаты > 2: ";
    	it2->Out();
    	cout << endl;
	}

	//Создайте список из указателей на элеметы Vector. С помощью 
	//алгоритма find_if() и предиката (можно использовать предикат - 
	//метод класса Vector, определенный в предыдущем задании) найдите в
	//последовательности элемент, удовлетворяющий условию

	list<Vector*> lp = {new Vector(1,1), new Vector(5,5)};

	auto it3 = find_if(lp.begin(), lp.end(), [](Vector* v){
		return bothGreaterThan2(*v);
	});

	if(it3 != lp.end()){
    	cout << "Элемент в списке указателей: ";
    	(*it3)->Out();  // разыменовываем указатель
    	cout << endl;
	}

	//5в. Создайте список элементов Vector. Наполните список
	//значениями. С помощью алгоритма replace() замените элемент
	//с определенным значением новым значением. С помощью алгоритма
	//replace_if() замените элемент, удовлетворяющий какому-либо
	//условию на определенное значение. Подсказка: условие
	//задается предикатом.

	list<Vector> lrep = {Vector(1,1), Vector(2,2), Vector(3,3)};

	replace(lrep.begin(), lrep.end(), Vector(2,2), Vector(9,9));

	replace_if(lrep.begin(), lrep.end(), [](const Vector& v){
		return v.getX() < 2;
	}, Vector(0,0));

	pr(lrep, "List after replace_if");

  	//Сформировали значения элементов списка

	//5г. Создайте вектор строк (string). С помощью алгоритма count()
	//сосчитайте количество одинаковых строк. С помощью алгоритма
	//count_if() сосчитайте количество строк, начинающихся с заданной
	//буквы

	vector<string> vs = {"apple", "banana", "apple", "avocado", "apricot", "car", "autumn"};
	cout << "\ncount 'apple': " << count(vs.begin(), vs.end(), "apple");

	cout << "\ncount_if starts with a: " << count_if(vs.begin(), vs.end(), [](const string& s){
		return s[0] == 'a';
	});

	//5д. С помощью алгоритма count_if() сосчитайте количество строк,
	//которые совпадают с заданной строкой. Подсказка: смотри тему
	//объекты-функции
  string str;
  cin >>str;
	cout << "\ncount_if == avocado: " << count_if(vs.begin(), vs.end(), [&str](const string& s){
		return s == str;
	});


	cout <<"\n\n";
}