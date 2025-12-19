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
    cout << "\nПравило \"+1\" (Вариант 48):" << endl;
    cout << "  a+1=b  b+1=e  c+1=f  d+1=g" << endl;
    cout << "  e+1=d  f+1=h  g+1=c  h+1=a" << endl;
    cout << "  Последовательность: a->b->e->d->g->c->f->h->a (цикл)" << endl;
    cout << "============================================================" << endl << endl;
}

void printMenu() {
    cout << "\nВыберите операцию:" << endl;
    cout << "1. Сложение (+)" << endl;
    cout << "2. Вычитание (-)" << endl;
    cout << "3. Умножение (*)" << endl;
    cout << "4. Деление (÷)" << endl;
    cout << "5. Возведение в степень (^)" << endl;
    cout << "6. НОД (GCD)" << endl;
    cout << "7. НОК (LCM)" << endl;
    cout << "8. Запустить тесты" << endl;
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
        
        // Тест 2: Коммутативность сложения
        cout << "\n2. КОММУТАТИВНОСТЬ СЛОЖЕНИЯ (a + b = b + a):" << endl;
        BigFiniteNumber r1 = BigFiniteNumber("c") + BigFiniteNumber("d");
        BigFiniteNumber r2 = BigFiniteNumber("d") + BigFiniteNumber("c");
        cout << "   c + d = " << r1 << endl;
        cout << "   d + c = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "✓ OK" : "✗ FAIL") << endl;
        
        // Тест 3: Ассоциативность сложения
        cout << "\n3. АССОЦИАТИВНОСТЬ СЛОЖЕНИЯ ((a+b)+c = a+(b+c)):" << endl;
        r1 = (BigFiniteNumber("b") + BigFiniteNumber("c")) + BigFiniteNumber("d");
        r2 = BigFiniteNumber("b") + (BigFiniteNumber("c") + BigFiniteNumber("d"));
        cout << "   (b + c) + d = " << r1 << endl;
        cout << "   b + (c + d) = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "✓ OK" : "✗ FAIL") << endl;
        
        // Тест 4: Коммутативность умножения
        cout << "\n4. КОММУТАТИВНОСТЬ УМНОЖЕНИЯ (a × b = b × a):" << endl;
        r1 = BigFiniteNumber("c") * BigFiniteNumber("e");
        r2 = BigFiniteNumber("e") * BigFiniteNumber("c");
        cout << "   c × e = " << r1 << endl;
        cout << "   e × c = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "✓ OK" : "✗ FAIL") << endl;
        
        // Тест 5: Ассоциативность умножения
        cout << "\n5. АССОЦИАТИВНОСТЬ УМНОЖЕНИЯ ((a×b)×c = a×(b×c)):" << endl;
        r1 = (BigFiniteNumber("b") * BigFiniteNumber("c")) * BigFiniteNumber("d");
        r2 = BigFiniteNumber("b") * (BigFiniteNumber("c") * BigFiniteNumber("d"));
        cout << "   (b × c) × d = " << r1 << endl;
        cout << "   b × (c × d) = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "✓ OK" : "✗ FAIL") << endl;
        
        // Тест 6: Дистрибутивность
        cout << "\n6. ДИСТРИБУТИВНОСТЬ (a×(b+c) = a×b + a×c):" << endl;
        r1 = BigFiniteNumber("c") * (BigFiniteNumber("b") + BigFiniteNumber("d"));
        r2 = (BigFiniteNumber("c") * BigFiniteNumber("b")) + (BigFiniteNumber("c") * BigFiniteNumber("d"));
        cout << "   c × (b + d) = " << r1 << endl;
        cout << "   c × b + c × d = " << r2 << endl;
        cout << "   Результат: " << (r1 == r2 ? "✓ OK" : "✗ FAIL") << endl;
        
        // Тест 7: Свойство x * a = a
        cout << "\n7. СВОЙСТВО x × a = a:" << endl;
        cout << "   b × a = " << (BigFiniteNumber("b") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        cout << "   c × a = " << (BigFiniteNumber("c") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        cout << "   h × a = " << (BigFiniteNumber("h") * BigFiniteNumber("a")) << " (ожидается: a)" << endl;
        
        // Тест 8: Деление положительных
        cout << "\n8. ДЕЛЕНИЕ ПОЛОЖИТЕЛЬНЫХ:" << endl;
        auto [q1, r1_div] = BigFiniteNumber("e").divide(BigFiniteNumber("b"));
        cout << "   e ÷ b = " << q1 << "(" << r1_div << ")" << endl;
        
        auto [q2, r2_div] = BigFiniteNumber("h").divide(BigFiniteNumber("c"));
        cout << "   h ÷ c = " << q2 << "(" << r2_div << ")" << endl;
        
        // Тест 9: Деление отрицательного на положительное
        cout << "\n9. ДЕЛЕНИЕ ОТРИЦАТЕЛЬНОГО НА ПОЛОЖИТЕЛЬНОЕ:" << endl;
        auto [q3, r3] = BigFiniteNumber("-h").divide(BigFiniteNumber("c"));
        cout << "   -h ÷ c = " << q3 << "(" << r3 << ")" << endl;
        cout << "   (остаток скорректирован по правилу)" << endl;
        
        // Тест 10: Специальные случаи деления
        cout << "\n10. СПЕЦИАЛЬНЫЕ СЛУЧАИ ДЕЛЕНИЯ:" << endl;
        try {
            auto [q4, r4] = BigFiniteNumber("c").divide(BigFiniteNumber("a"));
            cout << "   c ÷ a = " << q4 << "(" << r4 << ")" << endl;
        } catch (const domain_error& e) {
            cout << "   c ÷ a = " << e.what() << " (деление на ноль)" << endl;
        }
        
        try {
            auto [q5, r5] = BigFiniteNumber("a").divide(BigFiniteNumber("a"));
            cout << "   a ÷ a = " << q5 << "(" << r5 << ")" << endl;
        } catch (const domain_error& e) {
            cout << "   a ÷ a = " << e.what() << " (0÷0)" << endl;
        }
        
        // Тест 11: Возведение в степень
        cout << "\n11. ВОЗВЕДЕНИЕ В СТЕПЕНЬ:" << endl;
        cout << "   b ^ c = " << BigFiniteNumber("b").power(BigFiniteNumber("c")) << endl;
        cout << "   c ^ b = " << BigFiniteNumber("c").power(BigFiniteNumber("b")) << endl;
        cout << "   c ^ c = " << BigFiniteNumber("c").power(BigFiniteNumber("c")) << endl;
        
        // Тест 12: НОД и НОК
        cout << "\n12. НОД И НОК:" << endl;
        cout << "   НОД(e, c) = " << BigFiniteNumber::gcd(BigFiniteNumber("e"), BigFiniteNumber("c")) << endl;
        cout << "   НОК(e, c) = " << BigFiniteNumber::lcm(BigFiniteNumber("e"), BigFiniteNumber("c")) << endl;
        cout << "   НОД(h, d) = " << BigFiniteNumber::gcd(BigFiniteNumber("h"), BigFiniteNumber("d")) << endl;
        cout << "   НОК(h, d) = " << BigFiniteNumber::lcm(BigFiniteNumber("h"), BigFiniteNumber("d")) << endl;
        
    } catch (const exception& e) {
        cout << "Ошибка при тестировании: " << e.what() << endl;
    }
    
    cout << "\n============================================================" << endl;
}

int main() {
    // Инициализация таблиц
    init_symbols_maps();
    
    printHeader();
    
    int choice;
    string num1_str, num2_str;
    
    while (true) {
        printMenu();
        cout << "\nВаш выбор: ";
        cin >> choice;
        
        if (choice == 0) {
            cout << "\nЗавершение работы..." << endl;
            break;
        }
        
        if (choice == 8) {
            runTests();
            continue;
        }
        
        if (choice < 1 || choice > 7) {
            cout << "Неверный выбор!" << endl;
            continue;
        }
        
        cout << "Введите первое число: ";
        cin >> num1_str;
        
        if (choice <= 7) {
            if (choice == 5) {
                cout << "Введите степень: ";
            } else if (choice == 6 || choice == 7) {
                cout << "Введите второе число: ";
            } else {
                cout << "Введите второе число: ";
            }
            cin >> num2_str;
        }
        
        try {
            BigFiniteNumber num1(num1_str);
            BigFiniteNumber num2(num2_str);
            
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
                    cout << "\nРезультат: " << num1 << " × " << num2 << " = " << result << endl;
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
                case 5: {
                    BigFiniteNumber result = num1.power(num2);
                    cout << "\nРезультат: " << num1 << " ^ " << num2 << " = " << result << endl;
                    break;
                }
                case 6: {
                    BigFiniteNumber result = BigFiniteNumber::gcd(num1, num2);
                    cout << "\nРезультат: НОД(" << num1 << ", " << num2 << ") = " << result << endl;
                    break;
                }
                case 7: {
                    BigFiniteNumber result = BigFiniteNumber::lcm(num1, num2);
                    cout << "\nРезультат: НОК(" << num1 << ", " << num2 << ") = " << result << endl;
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
