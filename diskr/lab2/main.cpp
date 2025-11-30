// main.cpp
#include "BooleanFunction.h"
#include <iostream>
#include <bitset>

using namespace std;

const int FUNCTION_VALUE = 20986;

int main() {
    cout << "Вариант 48: f = " << FUNCTION_VALUE << "\n";
    cout << "Двоичное: " << bitset<16>(FUNCTION_VALUE) << "\n\n";

    BooleanFunction f(FUNCTION_VALUE);

    f.printTruthTable();
    cout << "\nСДНФ f:\n" << f.buildSDNF() << "\n";
    cout << "\nСКНФ f:\n" << f.buildSKNF() << "\n";

    f.buildBDD();

    auto z = f.buildZhegalkin();
    cout << "\nПолином Жегалкина:\n";
    f.printZhegalkin(z);

    cout << "\nПроверка значений:\n";
    while (true) {
        cout << "x1 x2 x3 x4 (-1 для выхода): ";
        int x1; cin >> x1;
        if (x1 == -1) break;
        int x2, x3, x4; cin >> x2 >> x3 >> x4;
        int v1 = f.getValue(x1,x2,x3,x4);
        int v2 = f.evaluateBDD(x1,x2,x3,x4);
        int v3 = f.evaluateZhegalkin(z,x1,x2,x3,x4);
        cout << "→ " << v1 << " | " << v2 << " | " << v3 << (v1==v2&&v2==v3 ? " OK\n" : " ERROR\n");
    }
    return 0;
}