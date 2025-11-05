// Контейнеры STL: 
//deque, stack, queue, priority_queue
//set, multiset, map, multimap
//Итераторы. Стандартные алгоритмы. Предикаты.

#include "../lab3/MyString.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <type_traits> // is_same_v
#include <string>

using namespace std;	
#define stop asm("nop");

//============= Шаблон функции для вывода с помощью итератора
template <class T> void pr(T& v, string s)
{
	cout<<"\n\n\t"<<s<<" # Sequence:\n";
	
	// Итератор любого контейнера
	typename T::iterator p;
	int i;

	for (p = v.begin(), i=0;  p != v.end();  p++, i++)
		cout << endl << i+1 <<". "<< *p;
	cout << '\n';
}

//============= Шаблон функции для вывода queue, priority_queue, stack
template <typename T> void pr2(const T& container, const string& s) {
    cout << "\n\n\t" << s << " # Sequence:\n";
    T temp = container;
    int i = 0;
    while (!temp.empty()) {
        if constexpr (is_same_v<typename T::container_type, list<Point*>> || 
                      is_same_v<typename T::value_type, Point*>) {
            const Point* p = temp.front();
            cout << i + 1 << ". x: " << p->getX() << ", y: " << p->getY() << endl;
            temp.pop();
        } else if constexpr (is_same_v<T, stack<typename T::value_type>>) {
            cout << i + 1 << ". " << temp.top() << endl;
            temp.pop();
        } else {
            // Обработка priority_queue и других с top()
            using val_t = decltype(temp.top());
            if constexpr (is_same_v<val_t, const char*>) {
                const char* str = temp.top();
                cout << "Debug: Top pointer = " << (void*)str << endl;
                cout << i + 1 << ". " << (str ? str : "(null)") << endl << flush;
            } else {
                cout << i + 1 << ". " << temp.top() << endl;
            }
            temp.pop();
        }
        ++i;
    }
    cout << '\n';
}



// Компаратор для сравнения const char*
struct komparator{
    bool operator()(const char* a, const char* b) const{
        return strcmp(a, b) < 0; // Сравнение по содержимому строк
    }
};

int main()
{

	//Очередь с двумя концами - контейнер deque

	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать

	deque<Point> dq;
	vector<Point> vec = {{1, 3}, {2, 4}, {0, 7}};
	dq.assign(vec.begin(), vec.end());

	pr(dq, "Deque.assign(vec.begin(), vec.end())");

	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'

	deque<MyString> myStr;
	myStr.push_back(MyString("apple"));
	myStr.push_back(MyString("orange"));
	myStr.push_front(MyString("banana"));
	myStr.push_front(MyString("apricot"));
	myStr.insert(myStr.begin() + 1, MyString("Afrodita"));

	auto it = myStr.begin();
	while (it != myStr.end()){
    	const char* s = it->GetString();

    	if (s && (s[0] == 'A' || s[0] == 'a')){
        	it = myStr.erase(it);  // erase возвращает итератор на следующий элемент
    	} else {
        	++it;
    	}
	}

	pr(myStr, "After erase strings starting with A/a");

	////////////////////////////////////////////////////////////////////////////////////


	//Напишите шаблон функции для вывода значений stack, queue, priority_queue
	//Подумайте, как "получать" данное "с верхушки"?
	//Что происходит с контейнерами после вывода значений?

	// stack и priority_queue основана на доступе к "вершине" (последнему или максимальному элементу)
	// тогда как у queue приоритет — на "переднем" элементе (первом в очереди)

	////////////////////////////////////////////////////////////////////////////////////
	//stack

	//Создайте стек таким образом, чтобы
	//а) элементы стека стали копиями элементов вектора
	//б) при выводе значений как вектора, так и стека порядок значений был одинаковым 

	// Создаём стек, копируя элементы вектора в обратном порядке
    std::stack<Point> stk;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it){
        stk.push(*it);  // Копируем элементы
    }

	pr(vec, "Elements of vector");
	pr2(stk, "Elements of stack");

	//Сравнение и копирование стеков
	//а) создайте стек и любым способом задайте значения элементов
	//б) создайте новый стек таким образом, чтобы он стал копией первого
	//в) сравните стеки на равенство
	//г) модифицируйте любой из стеком любым образом (push, pop, top)
	//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)

	{
	stack<int> integerStack; // а)
	integerStack.push(1);
    integerStack.push(2);
    integerStack.push(4);
    integerStack.push(5);
    integerStack.push(199);
	pr2(integerStack, "Stack with elements of integer (original)");

	stack<int> integerStackCopy = integerStack; // б)
	pr2(integerStackCopy, "Stack with elements of integer (copy)");

	if (integerStack == integerStackCopy){ // в)
        cout << "Стеки равны" << endl;
    } else {
        cout << "Стеки не равны" << endl;
    }

	integerStack.push(300); // г)

	if (integerStack > integerStackCopy){ // д)
        cout << "integerStack больше integerStackCopy" << endl;
    } else if (integerStack < integerStackCopy){
        cout << "integerStack меньше integerStackCopy" << endl;
    } else {
        cout << "Стеки равны" << endl;
    }

	pr2(integerStack, "Stack with elements of integer (original) after push 1 element");
    }

	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?

	{
		// Создаём очередь с указателями на Point
        queue<Point*, std::list<Point*>> que; // list как базовый контейнер

        // Создаём объекты Point динамически и добавляем указатели в очередь
        que.push(new Point(1.0, 2.0));
        que.push(new Point(3.0, 4.0));
        que.push(new Point(5.0, 6.0));

        // Вывод исходной очереди
        pr2(que, "Initial queue");

        // Изменение значений первого и последнего элементов
        if (!que.empty()) {
            que.front()->setX(10.0); // Изменяем x первого элемента
            que.front()->setY(20.0);
            (*que.back()).setX(40.7);
            que.back()->setY(60.0);
        }

        // Вывод изменённой очереди
        pr2(que, "Queue after modification");

        // Освобождение памяти (важно, так как объекты созданы с new)
        while (!que.empty()) {
            delete que.front(); // Освобождаем память
            que.pop();          // Удаляем указатель из очереди
        }
	}

	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?

	{ // по умолчанию сравниваются адреса, а не строки
		const char* arr[] = {"qq", "gl", "ff", "gg", "nt"};
    	priority_queue<const char*, vector<const char*>, komparator> pque;

    	for (const char* str : arr){
        	pque.push(str);
        	// cout << "Pushed: " << str << endl;
    	}
		// cout << "Debug: Original queue size = " << pque.size() << endl;
    	pr2(pque, "Elements of priority_queue");
	}
	
	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)

	set<Point> setOfP; // а) operator < необходимо определить
	Point p1(0, 2);
	Point p2(1, 3);
	Point p3(4, 5);
	setOfP.insert(p1);
    setOfP.insert(p2);
    setOfP.insert(p3);

    pr(setOfP, "Elements of set<Point> # Sequence:");// б)

	// в)
	// Комментарий: Элементы в set нельзя изменять напрямую, так как это нарушит порядок

    set<int> set1 = {3, 1, 4, 1, 5}; // г)
    set<int> set2 = {5, 4, 3, 2, 1};
	pr(set1, "Set1 elements"); // Дубликаты игнорируются
	pr(set2, "Set2 elements");

	int array[] = {1, 2, 2, 3, 4, 5, 6, 2, 4}; // д
	set<int> set3;
	set3.insert(array, array + 9);
	pr(set3, "Set3 elements");
	// Дубли игнорируются, так как set содержит только уникальные элементы без повторов

	////////////////////////////////////////////////////////////////////////////////////
	//multiset

	multiset<int> multiSet1 = {3, 1, 4, 1, 5}; // г)
    multiset<int> multiSet2 = {5, 4, 3, 2, 1};
	pr(set1, "Multiset1 elements"); // Дубликаты игнорируются
	pr(set2, "MultiSet2 elements");

	////////////////////////////////////////////////////////////////////////////////////
	//map	
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")

	map<const char*, int, komparator> map1; // а)

	map1["Иванова"] = 52000; // б)
	map1["Адиатуллин"] = 250000;
	map1["Хасанаторов"] = 150000;

	map1.insert(make_pair("Петров", 61000));
	
	cout << "\n\tSalary map:\n"; // в)
	for(const auto& pair : map1){ // ключ константный у map
		cout << pair.first << ": " << pair.second << " руб.\n";
	}

	// e) ключи в нашем случае это фамилии константы, поэтому надо удалить старое и добавить новое
	int ivanovaCash = map1["Иванова"]; // сохраняем зп
	map1.erase("Иванова");
	map1.insert(make_pair("Петрова", ivanovaCash)); // добавляем новую значением по ключу (см. выше)

	cout << "\n\tSalary map after key change:\n"; // в)
	for(const auto& pair : map1){ // ключ константный у map
		cout << pair.first << ": " << pair.second << " руб.\n";
	}

	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью 
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()

	multimap<string, string> multimap1; // a)

	multimap1.insert(make_pair("computer", "персональный компьютер")); // б)
	multimap1.insert(make_pair("computer", "вычислительная машина"));
    multimap1.insert(make_pair("house", "дом"));
    multimap1.insert(make_pair("house", "здание"));
    multimap1.insert(make_pair("car", "автомобиль"));
	
	cout << "\n\tDictionary:\n"; // в)
	for(const auto &pair : multimap1){
		cout << pair.first << " - english, " << pair.second << " - русское значение.\n";
	}

	cout << "\n\tTranslations for 'house':\n"; // г)
	auto it_low = multimap1.lower_bound("house");
	auto it_up = multimap1.upper_bound("house");
	for(auto it = it_low; it != it_up; it++){
		cout << it->second << endl; // выводим только русское значение слова house
	}

///////////////////////////////////////////////////////////////////

	//Итераторы

	//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
	//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
	//являются копиями элементов set, но упорядочены по убыванию

	set<Point> pointSet;
	pointSet.insert(Point(1.7, 2.2));
	pointSet.insert(Point(1.7, 8.12));
	pointSet.insert(Point(6.6, 3.4));

	pr(pointSet, "Set with elements");

	vector<Point> pointVector(pointSet.rbegin(), pointSet.rend()); // rbegin() и rend() дают реверсивные итераторы для обратного порядка
    // по убыванию
	pr(pointVector, "Vector with elements");

	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.

	cout << "\n\tAlso set with elements\n";
	copy(pointSet.begin(), pointSet.end(), ostream_iterator<Point>(cout, " "));
	cout << endl;
	
	cout << "\n\tAlso vector with elements\n";
	copy(pointVector.begin(), pointVector.end(), ostream_iterator<Point>(cout, " "));
	cout << endl;

	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.

	vector<Point> vector1; // вставка в конец с вектор
	back_insert_iterator<vector<Point>> backIt = back_inserter(vector1);
	*backIt++ = Point(5.2, 6.1);
	*backIt++ = Point(5.1, 6.3);
	cout << "\n\tVector with back_inserter:\n";
    copy(vector1.begin(), vector1.end(), ostream_iterator<Point>(cout, " "));
    cout << endl;

	deque<Point> pointDeque; // вставка в начало с deque
	front_insert_iterator<deque<Point>> frontIt = front_inserter(pointDeque);
	*frontIt++ = Point(9.11, 8.12);
	*frontIt++ = Point(11.1, 22.2);
	cout << "\n\tDeque with front_inserter:\n";
    copy(pointDeque.begin(), pointDeque.end(), ostream_iterator<Point>(cout, " "));
    cout << endl;

	set<Point> pointSetik; // вставка с set
	insert_iterator<set<Point>> insertIt = inserter(pointSetik, pointSetik.begin());
	*insertIt++ = Point(3.22, 123);
	*insertIt++ = Point(8, 1.2);
	cout << "\n\tNew set with inserter:\n";
    copy(pointSetik.begin(), pointSetik.end(), ostream_iterator<Point>(cout, " "));
    cout << endl;

///////////////////////////////////////////////////////////////////

	//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

	// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
	//(массив, vector, list...)
	//С помощью алгоритма for_each в любой последовательности с элементами любого типа
	//распечатайте значения элементов
	//Подсказка : неплохо вызываемую функцию определить как шаблон



	stop

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката




	//С помощью алгоритма find() найдите в любой последовательности элементов Point
	//все итераторы на элемент Point с указанным значением.



	
	
	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
	////По умолчанию алгоритм сортирует последовательность по возрастанию.
	//Что должно быть определено в классе Point?
	// Замечание: обобщенный алгоритм sort не работает со списком, так как
	//это было бы не эффективно => для списка сортировка реализована методом класса!!!
	



	//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
	//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
	//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
	//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
	//[-n, +m].



	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.
	






	{//transform
		//Напишите функцию, которая с помощью алгоритма transform переводит 
		//содержимое объекта string в нижний регистр.
		//Подсказка: класс string - это "почти" контейнер, поэтому для него
		// определены методы begin() и end()


		//Заполните list объектами string. С помощью алгоритма transform сформируте
		//значения "пустого" set, конвертируя строки в нижний регистр
	
		list<string> strList = {"New", "Light", "Child", "DARK", "PRINCE"};

		// Преобразование строк в нижний регистр и заполнение set
        set<string> strSet;
        for (string& str : strList){
            toLowerCase(str); // Преобразуем строку в нижний регистр
            strSet.insert(str);// Добавляем в set
        }

		cout << "\n\tSet with lowercase strings:\n";
        for (const auto& str : strSet){
            cout << str << "\n";
        }
    }

	{// map
		
		//Сформируйте любым способом вектор с элементами типа string.
		//Создайте (и распечатайте для проверки) map<string, int>, который будет
		//содержать упорядоченные по алфавиту строки и
		//количество повторений каждой строки в векторе
	
		vector<string> vector2 = {"Toxis", "Ugly", "Stephan", "Dallas", "Bando", "Bando", "Dallas"};
		cout << "\n\tVector of strings\n";
        for (const auto& str : vector2){
            cout << str << "\n";
        }

		map<string, int> map2;
		for(const auto& str : vector2){
			map2[str]++; // Увеличиваем счётчик для каждой строки
		}
		cout << "\n\tMap with strings' count\n";
		for(const auto& pair : map2){
			cout << pair.first << ": " << pair.second << " \n";
		}
	}
	return 0;
}

