#include "BigFiniteNumber.h"
#include "constants.h"
#include "utils.h"
#include "arithmetic.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printHeader() {
    cout << "============================================================" << endl;
    cout << "    КАЛЬКУЛЯТОР КОНЕЧНОЙ АРИФМЕТИКИ (Вариант 48)" << endl;
    cout << "============================================================" << endl;
    cout << "Система счисления: Z₈ = {a, b, c, d, e, f, g, h}" << endl;
    cout << "Аддитивная единица (0): " << get_additive_unit() << endl;
    cout << "Мультипликативная единица (1): " << get_multiplicative_unit() << endl;
    cout << "Максимальная длина числа: " << MAX_DIGITS << " разрядов" << endl;
    cout << "  Последовательность: a->b->e->d->g->c->f->h->a" << endl;
    cout << "============================================================" << endl << endl;
}

void printMenu() {
    cout << "\nВыберите операцию:" << endl;
    cout << "1. Сложение (+)" << endl;
    cout << "2. Вычитание (-)" << endl;
    cout << "3. Умножение (*)" << endl;
    cout << "4. Деление (÷)" << endl;
    cout << "5. Запустить тесты" << endl;
    cout << "0. Выход" << endl;
}

void runTests() {
    cout << "\n============================================================" << endl;
    cout << "              ТЕСТИРОВАНИЕ КАЛЬКУЛЯТОРА" << endl;
    cout << "============================================================" << endl;
    
    try {
        // Тест 1: Проверка правила "+1"
        cout << "\n1. ПРОВЕРКА ПРАВИЛА \"+1\" (Вариант 48):" << endl;
        BigFiniteNumber one("b");
        cout << "   a + b = " << (BigFiniteNumber("a") + one) << " (ожидается: b)" << endl;
        cout << "   b + b = " << (BigFiniteNumber("b") + one) << " (ожидается: e)" << endl;
        cout << "   c + b = " << (BigFiniteNumber("c") + one) << " (ожидается: f)" << endl;
        cout << "   d + b = " << (BigFiniteNumber("d") + one) << " (ожидается: g)" << endl;
        cout << "   e + b = " << (BigFiniteNumber("e") + one) << " (ожидается: d)" << endl;
        cout << "   f + b = " << (BigFiniteNumber("f") + one) << " (ожидается: h)" << endl;
        cout << "   g + b = " << (BigFiniteNumber("g") + one) << " (ожидается: c)" << endl;
        cout << "   h + b = " << (BigFiniteNumber("h") + one) << " (ожидается: a → ba)" << endl;
        
        cout << "\n2. Коммутативность сложения (a + b = b + a):" << endl;
        BigFiniteNumber r1 = BigFiniteNumber("c") + BigFiniteNumber("d");
        BigFiniteNumber r2 = BigFiniteNumber("d") + BigFiniteNumber("c");
        cout << "   c + d = " << r1 << endl;
        cout << "   d + c = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "OK" : "Error") << endl;
        
        // Тест 3
        cout << "\n3. Ассоциативность ((a+b)+c = a+(b+c)):" << endl;
        r1 = (BigFiniteNumber("b") + BigFiniteNumber("c")) + BigFiniteNumber("d");
        r2 = BigFiniteNumber("b") + (BigFiniteNumber("c") + BigFiniteNumber("d"));
        cout << "   (b + c) + d = " << r1 << endl;
        cout << "   b + (c + d) = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "OK" : "Error") << endl;
        
        // Тест 4
        cout << "\n4. Коммутативность умножения (a * b = b * a):" << endl;
        r1 = BigFiniteNumber("c") * BigFiniteNumber("e");
        r2 = BigFiniteNumber("e") * BigFiniteNumber("c");
        cout << "   c * e = " << r1 << endl;
        cout << "   e * c = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "OK" : "Error") << endl;
        
        // Тест 5
        cout << "\n5. Ассоциативность умножения ((a*b)*c = a*(b*c)):" << endl;
        r1 = (BigFiniteNumber("b") * BigFiniteNumber("c")) * BigFiniteNumber("d");
        r2 = BigFiniteNumber("b") * (BigFiniteNumber("c") * BigFiniteNumber("d"));
        cout << "   (b * c) * d = " << r1 << endl;
        cout << "   b * (c * d) = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "OK" : "Error") << endl;
        
        // Тест 6
        cout << "\n6. Дистрибутивность (a*(b+c) = a*b + a*c):" << endl;
        r1 = BigFiniteNumber("c") * (BigFiniteNumber("b") + BigFiniteNumber("d"));
        r2 = (BigFiniteNumber("c") * BigFiniteNumber("b")) + (BigFiniteNumber("c") * BigFiniteNumber("d"));
        cout << "   c * (b + d) = " << r1 << endl;
        cout << "   c * b + c * d = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "OK" : "Error") << endl;
        
        // Тест 7
        cout << "\n7. Свойство x * a = a:" << endl;
        cout << "   b * a = " << (BigFiniteNumber("b") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        cout << "   c * a = " << (BigFiniteNumber("c") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        cout << "   h * a = " << (BigFiniteNumber("h") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        
    } catch (const exception& e) {
        cout << "Ошибка при тестировании: " << e.what() << endl;
    }
    
    cout << "\n============================================================" << endl;
}

int main() {
    init_symbols_maps(); // Инициализация таблиц
    
    printHeader();
    
    int choice;
    string num1_str, num2_str;
    
    while (true) {
        printMenu();
        cout << "\nВаш выбор: ";
        
        if (!(cin >> choice)) { // Проверка корректности ввода
            cout << "Ошибка ввода! Введите число от 0 до 5." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (choice == 0) {
            cout << "\nЗавершение работы..." << endl;
            break;
        }
        
        if (choice == 5) {
            runTests();
            continue;
        }
        
        if (choice < 1 || choice > 4) {
            cout << "Неверный выбор! Введите число от 0 до 5." << endl;
            continue;
        }
        
        cout << "Введите первое число: ";
        cin >> num1_str;
        cout << "Введите второе число: ";
        cin >> num2_str;
        
        try {
            BigFiniteNumber num1(num1_str);
            BigFiniteNumber num2(num2_str);
            
            cin.clear(); // Очистка буфера после успешного ввода
            cin.ignore(10000, '\n');
            
            string operation;
            switch (choice) {
                case 1: {
                    BigFiniteNumber result = num1 + num2;
                    cout << "\nРезультат: " << num1 << " + " << num2 << " = " << result << endl;
                    break;
                }
                case 2: {
                    BigFiniteNumber result = num1 - num2;
                    cout << "\nРезультат: " << num1 << " - " << num2 << " = " << result << endl;
                    break;
                }
                case 3: {
                    BigFiniteNumber result = num1 * num2;
                    cout << "\nРезультат: " << num1 << " * " << num2 << " = " << result << endl;
                    break;
                }
                case 4: {
                    try {
                        auto [quotient, remainder] = num1.divide(num2);
                        cout << "\nРезультат: " << num1 << " ÷ " << num2 << " = " 
                             << quotient << "(" << remainder << ")" << endl;
                    } catch (const domain_error& e) {
                        cout << "\nРезультат: " << num1 << " ÷ " << num2 << " = " << e.what() << endl;
                    }
                    break;
                }
            }
            
        } catch (const overflow_error& e) {
            cout << "\n⚠ ОШИБКА ПЕРЕПОЛНЕНИЯ: " << e.what() << endl;
        } catch (const invalid_argument& e) {
            cout << "\n⚠ ОШИБКА ВВОДА: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "\n⚠ ОШИБКА: " << e.what() << endl;
        }
    }
    
    return 0;
}
