#include "other.h"
#include <random>
#include <chrono>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

// Читает непустую строку
string readLineNonEmpty(const string& prompt){
    string s;
    while (true){
        cout << prompt;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "Ошибка: ввод не должен быть пустым\n";
    }
}

// Пытается распарсить целое из строки. Возвращает true и записывает результат в out, если строка
// состоит ровно из целого (без лишних символов).
bool parseLong(const string& str, long long& out){
    stringstream ss(str);
    long long v;
    if (!(ss >> v)) return false; // проверка на то, что у нас присутсвуют только числа из диапазона long long
    char c;
    if (ss >> c) return false; // убедиться, что после числа нет других символов (кроме пробелов)
    out = v;
    return true;
}

// Читает long long в диапазоне [min, max]
long long readLongInRange(const string& prompt, long long min, long long max){
    while (true){
        string s = readLineNonEmpty(prompt);  //выполняем запросы через getline
        long long v;
        if (!parseLong(s, v) || v < min || v > max){
            cout << "Ошибка: введите целое число от " << min << " до " << max << "\n";
            continue;
        }
        return v;
    }
}

void fillManual(MultiSet& ms, const GrayUniverse& U){ // ручной ввод в мультимножество
    if (U.size() == 0){
        cout << "Универсум пустой\n";
        return;
    }

    cout << "Ручной ввод: введите индекс (0.." << U.size()-1 << ") или код, или 'done'\n";
    while (true){
        string s = readLineNonEmpty("-> ");
        if (s == "done") break;

        long long idx;
        if (parseLong(s, idx)){
            if (idx < 0 || static_cast<size_t>(idx) >= U.size()){
                cout << "Ошибка: индекс вне диапазона (0.." << U.size()-1 << ")\n";
                continue;
            }
            long long mult = readLongInRange("Кратность: ", 1, 1000000);
            string code = U.atIndex(static_cast<size_t>(idx));
            ms.add(U, code, mult);
            cout << "Добавлено " << code << " x" << mult << "\n";
        } else{
            if (!U.contains(s)){
                cout << "Код не в универсум или неверной длины\n";
                continue;
            }
            long long mult = readLongInRange("Кратность: ", 1, 1000000);
            ms.add(U, s, mult);
            cout << "Добавлено " << s << " x" << mult << "\n";
        }
    }
}

// Упрощённый автозаполнение
void fillAuto(MultiSet& ms, const GrayUniverse& U) {
    if (U.size() == 0) {
        cout << "Универсум пустой — нечего добавлять\n";
        return;
    }

    long long total = readLongInRange("Введите общее количество элементов: ", 0, 1000000);
    if (total == 0) {
        ms.clear();
        cout << "Мультимножество очищено\n";
        return;
    }

    long long maxMult = readLongInRange("Максимальная кратность: ", 1, 1000000);

    random_device rd;
    mt19937_64 rng(rd());
    uniform_int_distribution<int> distMult(1, static_cast<int>(maxMult));

    // Получаем список всех кодов из универсума
    vector<Code> allCodes;
    for (const auto& [code, _] : U.all()) {
        allCodes.push_back(code);
    }

    // Перемешиваем и выбираем первые total уникальных кодов
    shuffle(allCodes.begin(), allCodes.end(), rng);
    if ((size_t)total > allCodes.size()) total = allCodes.size();

    for (int i = 0; i < total; ++i) {
        Code code = allCodes[i];
        int m = distMult(rng);
        ms.add(U, code, m);
    }

    cout << "Автозаполнение завершено\n";
}
