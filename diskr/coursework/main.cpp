#include "finite_arithmetic.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printHeader() {
    cout << "============================================================" << endl;
    cout << "    КАЛЬКУЛЯТОР КОНЕЧНОЙ АРИФМЕТИКИ (Вариант 48)" << endl;
    cout << "============================================================" << endl;
    cout << "Система счисления: Z₈ = {" << FiniteArithmetic::getAlphabet() << "}" << endl;
    cout << "Аддитивная единица (0): " << FiniteArithmetic::getAdditiveIdentity() << endl;
    cout << "Мультипликативная единица (1): " << FiniteArithmetic::getMultiplicativeIdentity() << endl;
    cout << "Максимальная длина числа: " << FiniteArithmetic::getMaxLength() << " разрядов" << endl;
    cout << "============================================================" << endl << endl;
}

void printMenu() {
    cout << "\nВыберите операцию:" << endl;
    cout << "1. Сложение (+)" << endl;
    cout << "2. Вычитание (-)" << endl;
    cout << "3. Умножение (*)" << endl;
    cout << "4. Деление (÷)" << endl;
    cout << "5. Тесты" << endl;
    cout << "0. Выход" << endl;
}

void runTests(const FiniteArithmetic& calc) {
    cout << "\n============================================================" << endl;
    cout << "              ТЕСТИРОВАНИЕ КАЛЬКУЛЯТОРА" << endl;
    cout << "============================================================" << endl;
    
    try {
        // Тест 1: Сложение
        cout << "\n1. СЛОЖЕНИЕ:" << endl;
        cout << "   b + b = " << calc.add("b", "b") << " (ожидается: c)" << endl;
        cout << "   c + d = " << calc.add("c", "d") << " (ожидается: f)" << endl;
        cout << "   e + (-c) = " << calc.add("e", "-c") << " (ожидается: c)" << endl;
        cout << "   -e + (-c) = " << calc.add("-e", "-c") << " (ожидается: -h)" << endl;
        
        // Тест 2: Вычитание
        cout << "\n2. ВЫЧИТАНИЕ:" << endl;
        cout << "   e - c = " << calc.subtract("e", "c") << " (ожидается: c)" << endl;
        cout << "   c - e = " << calc.subtract("c", "e") << " (ожидается: -c)" << endl;
        
        // Тест 3: Умножение
        cout << "\n3. УМНОЖЕНИЕ:" << endl;
        cout << "   c * c = " << calc.multiply("c", "c") << " (ожидается: e)" << endl;
        cout << "   d * e = " << calc.multiply("d", "e") << " (ожидается: be)" << endl;
        cout << "   c * (-d) = " << calc.multiply("c", "-d") << " (ожидается: -g)" << endl;
        cout << "   c * a = " << calc.multiply("c", "a") << " (проверка свойства x*a=a)" << endl;
        
        // Тест 4: Деление положительных
        cout << "\n4. ДЕЛЕНИЕ ПОЛОЖИТЕЛЬНЫХ:" << endl;
        cout << "   g ÷ c = " << calc.divide("g", "c") << " (ожидается: d(a))" << endl;
        cout << "   h ÷ c = " << calc.divide("h", "c") << " (ожидается: d(b))" << endl;
        cout << "   ba ÷ e = " << calc.divide("ba", "e") << endl;
        
        // Тест 5: Деление отрицательного на положительное
        cout << "\n5. ДЕЛЕНИЕ ОТРИЦАТЕЛЬНОГО НА ПОЛОЖИТЕЛЬНОЕ:" << endl;
        cout << "   -h ÷ c = " << calc.divide("-h", "c") << " (ожидается: -d(c) по правилу -7÷3=-3(2))" << endl;
        cout << "   -g ÷ c = " << calc.divide("-g", "c") << " (ожидается: -d(a))" << endl;
        
        // Тест 6: Деление положительного на отрицательное
        cout << "\n6. ДЕЛЕНИЕ ПОЛОЖИТЕЛЬНОГО НА ОТРИЦАТЕЛЬНОЕ:" << endl;
        cout << "   h ÷ (-c) = " << calc.divide("h", "-c") << " (ожидается: -d(b))" << endl;
        
        // Тест 7: Специальные случаи деления
        cout << "\n7. СПЕЦИАЛЬНЫЕ СЛУЧАИ:" << endl;
        cout << "   c ÷ a = " << calc.divide("c", "a") << " (ожидается: Ø)" << endl;
        cout << "   a ÷ a = " << calc.divide("a", "a") << " (ожидается: диапазон)" << endl;
        
        // Тест 8: Свойства
        cout << "\n8. ПРОВЕРКА СВОЙСТВ:" << endl;
        string res1 = calc.add(calc.add("b", "c"), "d");
        string res2 = calc.add("b", calc.add("c", "d"));
        cout << "   Ассоциативность +: (b+c)+d = " << res1 << ", b+(c+d) = " << res2;
        cout << " → " << (res1 == res2 ? "OK" : "FAIL") << endl;
        
        string res3 = calc.multiply("c", calc.add("b", "d"));
        string res4 = calc.add(calc.multiply("c", "b"), calc.multiply("c", "d"));
        cout << "   Дистрибутивность: c*(b+d) = " << res3 << ", c*b+c*d = " << res4;
        cout << " → " << (res3 == res4 ? "OK" : "FAIL") << endl;
        
        // Тест 9: Переполнение
        cout << "\n9. ПРОВЕРКА ПЕРЕПОЛНЕНИЯ:" << endl;
        try {
            string maxNum(8, 'h');
            string result = calc.add(maxNum, "b");
            cout << "   " << maxNum << " + b = " << result << endl;
        } catch (const overflow_error& e) {
            cout << "   hhhhhhhh + b = ОШИБКА: " << e.what() << endl;
        }
        
    } catch (const exception& e) {
        cout << "Ошибка при тестировании: " << e.what() << endl;
    }
    
    cout << "\n============================================================" << endl;
}

int main() {
    FiniteArithmetic calc;
    printHeader();
    
    int choice;
    string num1, num2, result;
    
    while (true) {
        printMenu();
        cout << "\nВаш выбор: ";
        cin >> choice;
        
        if (choice == 0) {
            cout << "\nЗавершение работы..." << endl;
            break;
        }
        
        if (choice == 5) {
            runTests(calc);
            continue;
        }
        
        if (choice < 1 || choice > 4) {
            cout << "Неверный выбор!" << endl;
            continue;
        }
        
        cout << "Введите первое число: ";
        cin >> num1;
        cout << "Введите второе число: ";
        cin >> num2;
        
        try {
            string operation;
            switch (choice) {
                case 1:
                    result = calc.add(num1, num2);
                    operation = "+";
                    break;
                case 2:
                    result = calc.subtract(num1, num2);
                    operation = "-";
                    break;
                case 3:
                    result = calc.multiply(num1, num2);
                    operation = "*";
                    break;
                case 4:
                    result = calc.divide(num1, num2);
                    operation = "÷";
                    break;
            }
            
            cout << "\nРезультат: " << num1 << " " << operation << " " << num2 << " = " << result << endl;
            
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
