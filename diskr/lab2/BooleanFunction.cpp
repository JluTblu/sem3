#include "BooleanFunction.h"
#include <iostream>
using namespace std;

BooleanFunction::BooleanFunction(int funcValue) : root(nullptr){
    truthTable = bitset<16>(funcValue);
    term0 = new BDDNode(0, 0); // Создаем терминальные узлы
    term1 = new BDDNode(0, 1);
}
    
BooleanFunction::~BooleanFunction(){
    deleteBDD(root);
    delete term0;
    delete term1;
}
    
void BooleanFunction::deleteBDD(BDDNode* node){
    if (!node || node->var == 0) return; // Не удаляем терминалы
    deleteBDD(node->low);
    deleteBDD(node->high);
    delete node;
}

int BooleanFunction::getValue(int x1, int x2, int x3, int x4) const{
    int idx = (x1 << 3) | (x2 << 2) | (x3 << 1) | x4;
    return truthTable[15 - idx];
}

void BooleanFunction::printTruthTable() const{
    cout << "\n=== ТАБЛИЦА ИСТИННОСТИ ===\n";
    cout << "№  | x1 x2 x3 x4 | f\n";
    cout << "---|-------------|---\n";
    for (int i = 0; i < 16; ++i){
        int x1 = (i >> 3) & 1, x2 = (i >> 2) & 1, x3 = (i >> 1) & 1, x4 = i & 1;
        printf("%2d | %d  %d  %d  %d  | %d\n", i, x1, x2, x3, x4, getValue(x1,x2,x3,x4));
    }
}

string BooleanFunction::buildSDNF() const{
    vector<vector<int>> m;
    for (int i = 0; i < 16; ++i){
        int x1 = (i >> 3) & 1, x2 = (i >> 2) & 1, x3 = (i >> 1) & 1, x4 = i & 1;
        if (getValue(x1,x2,x3,x4)) m.push_back({x1,x2,x3,x4});
    }
    if (m.empty()) return "0";
    string s;
    for (size_t i = 0; i < m.size(); ++i){
        if (i) s += " ∨ ";
        s += "(";
        for (int j = 0; j < 4; ++j){
            if (j) s += "∧";
            if (!m[i][j]) s += "¬";
            s += "x" + to_string(j+1);
        }
        s += ")";
    }
    return s;
}

string BooleanFunction::buildSKNF() const{
    vector<vector<int>> m;
    for (int i = 0; i < 16; ++i){
        int x1 = (i >> 3) & 1, x2 = (i >> 2) & 1, x3 = (i >> 1) & 1, x4 = i & 1;
        if (!getValue(x1,x2,x3,x4)) m.push_back({x1,x2,x3,x4});
    }
    if (m.empty()) return "1";
    string s;
    for (size_t i = 0; i < m.size(); ++i){
        if (i) s += " ∧ ";
        s += "(";
        for (int j = 0; j < 4; ++j){
            if (j) s += "∨";
            if (m[i][j]) s += "¬";
            s += "x" + to_string(j+1);
        }
        s += ")";
    }
    return s;
}

vector<int> BooleanFunction::buildZhegalkin() const{
    vector<int> f(16);
    for (int i = 0; i < 16; ++i){
        int x1 = (i >> 3) & 1, x2 = (i >> 2) & 1, x3 = (i >> 1) & 1, x4 = i & 1;
        f[i] = getValue(x1,x2,x3,x4);
    }
    for (int i = 0; i < 4; ++i){
        int step = 1 << i;
        for (int j = 0; j < 16; ++j)
            if (j & step) f[j] ^= f[j ^ step];
    }
    return f;
}

void BooleanFunction::printZhegalkin(const vector<int>& c) const{
    bool first = true;
    for (int i = 0; i < 16; ++i){
        if (!c[i]) continue;
        if (!first) cout << " ⊕ ";
        first = false;
        if (i == 0){ cout << "1"; continue; }
        string t;
        if (i & 8) t += "x1";
        if (i & 4) t += (t.empty() ? "x2" : "∧x2");
        if (i & 2) t += (t.empty() ? "x3" : "∧x3");
        if (i & 1) t += (t.empty() ? "x4" : "∧x4");
        cout << t;
    }
    if (first) cout << "0";
    cout << endl;
}

int BooleanFunction::evaluateZhegalkin(const vector<int>& c, int x1, int x2, int x3, int x4) const{
    int res = 0;
    for (int i = 0; i < 16; ++i){
        if (!c[i]) continue;
        int term = 1;
        if (i & 8) term &= x1;
        if (i & 4) term &= x2;
        if (i & 2) term &= x3;
        if (i & 1) term &= x4;
        res ^= term;
    }
    return res;
}

BDDNode* BooleanFunction::buildRecursive(int level, int x1, int x2, int x3, int x4){
    if (level == 4){ // Если дошли до конца, возвращаем терминал
        return getValue(x1, x2, x3, x4) ? term1 : term0;
    }
        
    int var = level + 1; // 1, 2, 3, 4
    BDDNode* lo;
    BDDNode* hi;
        
    // Рекурсивно строим поддеревья
    if (var == 1){
        lo = buildRecursive(level + 1, 0, x2, x3, x4);
        hi = buildRecursive(level + 1, 1, x2, x3, x4);
    } else if (var == 2){
        lo = buildRecursive(level + 1, x1, 0, x3, x4);
        hi = buildRecursive(level + 1, x1, 1, x3, x4);
    } else if (var == 3){
        lo = buildRecursive(level + 1, x1, x2, 0, x4);
        hi = buildRecursive(level + 1, x1, x2, 1, x4);
    } else { // var == 4
        lo = buildRecursive(level + 1, x1, x2, x3, 0);
        hi = buildRecursive(level + 1, x1, x2, x3, 1);
    }
        
    if (lo == hi){
        return lo; // если обе ветви ведут к одному узлу, возвращаем его
    }
        
    BDDNode* node = new BDDNode(var); // Создаем новый узел
    node->low = lo;
    node->high = hi;
    return node;
}

void BooleanFunction::buildBDD(){
    root = buildRecursive(0, 0, 0, 0, 0);
}
    
int BooleanFunction::evaluateBDD(int x1, int x2, int x3, int x4) const{
    if (!root) return -1;
        
    BDDNode* current = root;
    int vars[4] = {x1, x2, x3, x4};
        
    while (current->var != 0){ // Идем по дереву до терминала
        int varIndex = current->var - 1; // 0, 1, 2, 3
        if (vars[varIndex] == 0){
            current = current->low;
        } else {
            current = current->high;
        }
    }
    return current->value;
}