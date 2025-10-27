#include <iostream>
#include <random>
#include "gray.h"
#include "multiset.h"
#include "other.h"

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    GrayUniverse U;
    MultiSet A, B;
    bool universeReady = false;

    while (true){
        cout << "\n=== Меню ===\n";
        cout << "1) Сгенерировать универсум (код Грея)\n";
        cout << "2) Заполнить A (ручной/авто)\n";
        cout << "3) Заполнить B (ручной/авто)\n";
        cout << "4) Показать универсум / A / B\n";
        cout << "5) Выполнить все операции и показать результаты\n";
        cout << "6) Очистить A и B\n";
        cout << "0) Выход\n";
        int cmd = (int) readLongInRange("Выберите пункт: ", 0, 10);

        if (cmd == 0) break;
        if (cmd == 1) {
            int nbits = (int) readLongInRange("Введите разрядность n (0..20 рекомендовано): ", 0, 20);
            try {
                size_t maxSize = 1ull << nbits;
                cout << "Максимальный размер универсума: " << maxSize << "\n";

                U.generateAuto((unsigned)nbits); // теперь мощность задаётся внутри generateAuto случайно

                A.clear();
                B.clear();
                universeReady = true;

                cout << "Универсум готов: " << U.size() << " уникальных кодов.\n";
                U.printUniverse(); // выводим коды и их кратности
            } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
} else if (cmd == 2){
            if (!universeReady){
                cout << "Сначала сгенерируйте универсум\n";
                continue; 
            }
            cout << "1) Ручной  2) Авто\n";
            int t = (int) readLongInRange("Выбор: ", 1, 2);
            if (t == 1) fillManual(A, U); 
            else fillAuto(A, U);
        } else if (cmd == 3){
            if (!universeReady){
                cout << "Сначала сгенерируйте универсум\n";
                continue;
            }
            cout << "1) Ручной  2) Авто\n";
            int t = (int) readLongInRange("Выбор: ", 1, 2);
            if (t == 1) fillManual(B, U);
            else fillAuto(B, U);
        } else if (cmd == 4){
            if (!universeReady){
                cout << "Универсум не задан\n";
                continue;
            }
            U.printUniverse();
            A.print("A");
            B.print("B");
        } else if (cmd == 5){
            if (!universeReady){
                cout << "Универсум не задан\n";
                continue;
            }
            A.print("A");
            B.print("B");
            A.set_union(B).print("Объединение (max)");
            A.set_inter(B).print("Пересечение (min)");
            A.set_diff(U, B).print("A - B");
            B.set_diff(U, A).print("B - A");
            A.set_symdiff(U, B).print("Симметрическая разность");
            MultiSet::complement(U, A).print("Дополнение U\\A");
            MultiSet::complement(U, B).print("Дополнение U\\B");
            A.add(B).print("Арифметическая сумма (a+b)");
            A.sub(B).print("Арифметическая разность (a-b)");
            A.mul(B).print("Арифметическое умножение (a*b, если < 0, результат не записываем)");
            A.div(B).print("Арифметическое деление(a/b, -1 = результат не определен, так как деление на 0)");
        } else if (cmd == 6){
            A.clear();
            B.clear();
            cout << "A и B очищены\n";
        } else{
            cout << "Неверный пункт\n";
        }
    }

    cout << "Конец\n";
    return 0;
}