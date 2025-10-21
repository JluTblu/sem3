#include "multiset.h"
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

MultiSet::MultiSet(){}

void MultiSet::clear(){
    m.clear();
}

bool MultiSet::empty() const{
    return m.empty();
}

void MultiSet::add(const GrayUniverse& U, const Code& c, Count k) {
    if (k == 0) return;
    Count maxAllowed = U.cardinality(c);
    if (maxAllowed == 0) return; // код не существует в универсуме

    Count current = m[c];
    Count toAdd = min(k, maxAllowed - current);
    if (toAdd > 0) m[c] += toAdd;
}

Count MultiSet::get(const Code& c) const{ // возвращает ключ, если такой элемент есть
    auto it = m.find(c);
    return it == m.end() ? 0 : it->second;
}

void MultiSet::print(const string& title) const {
    if (!title.empty()) cout << "=== " << title << " ===\n";
    if (m.empty()) {
        cout << "∅\n";
        return;
    }

    vector<pair<Code, Count>> V(m.begin(), m.end());
    sort(V.begin(), V.end());

    for (const auto& [code, count] : V) {
        if (count == -1)
            cout << code << " : деление на 0 — значение неопределено\n";
        else if (count == -2)
            cout << code << " : ошибка — отрицательная кратность невозможна\n";
        else
            cout << code << " : " << count << '\n';
    }
}


MultiSet MultiSet::set_union(const MultiSet& B) const{ // объединение
    MultiSet R = *this;
    for (const auto& p : B.m){
        R.m[p.first] = max(R.get(p.first), p.second);
    }
    return R;
}

MultiSet MultiSet::set_inter(const MultiSet& B) const{ // пересечение
    MultiSet R;
    for (const auto& p : m){
        Count v = min(p.second, B.get(p.first));
        if (v > 0){
            R.m[p.first] = v;
        }
    }
    return R;
}

MultiSet MultiSet::set_diff(const MultiSet& B) const{ // разность
    MultiSet R;
    for (const auto& p : m){
        Count v = p.second - B.get(p.first);
        if (v > 0) R.m[p.first] = v;
    }
    return R;
}

MultiSet MultiSet::set_symdiff(const MultiSet& B) const{ // симметрическая разность
    MultiSet R;
    set<Code> keys;
    for (const auto& p : m) keys.insert(p.first);
    for (const auto& p : B.m) keys.insert(p.first);
    for (const auto& k : keys){
        Count v = abs(static_cast<long long>(this->get(k)) - B.get(k));
        if (v > 0) R.m[k] = v;
    }
    return R;
}

MultiSet MultiSet::add(const MultiSet& B) const{ // арифметическая сумма
    MultiSet R;
    set<Code> keys;
    for (const auto& p : m) keys.insert(p.first);
    for (const auto& p : B.m) keys.insert(p.first);
    for (const auto& k : keys){
        Count v = this->get(k) + B.get(k);
        if (v != 0) R.m[k] = v;
    }
    return R;
}

MultiSet MultiSet::sub(const MultiSet& B) const {
    MultiSet R;
    set<Code> keys;
    for (const auto& p : m) keys.insert(p.first);
    for (const auto& p : B.m) keys.insert(p.first);

    for (const auto& k : keys) {
        long long v = static_cast<long long>(this->get(k)) - B.get(k);
        if (v > 0) {
            R.m[k] = static_cast<Count>(v);
        } else if (v < 0) {
            R.m[k] = -2; // маркер: отрицательная кратность невозможна
        }
        // если v == 0, не добавляем
    }

    return R;
}


MultiSet MultiSet::mul(const MultiSet& B) const{ // поэлементное умножение
    MultiSet R;
    set<Code> keys;
    for (const auto& p : m) keys.insert(p.first);
    for (const auto& p : B.m) keys.insert(p.first);
    for (const auto& k : keys){
        Count v = this->get(k) * B.get(k);
        if (v != 0) R.m[k] = v;
    }
    return R;
}

MultiSet MultiSet::div(const MultiSet& B) const {
    MultiSet R;
    set<Code> keys;
    for (const auto& p : m) keys.insert(p.first);
    for (const auto& p : B.m) keys.insert(p.first);

    for (const auto& k : keys) {
        Count a = this->get(k), b = B.get(k);
        if (b == 0) {
            if (a != 0) R.m[k] = -1; // маркер: деление на ноль
        } else {
            Count v = a / b;
            if (v != 0) R.m[k] = v;
        }
    }

    return R;
}


MultiSet MultiSet::complement(const GrayUniverse& U, const MultiSet& A) {
    MultiSet R;
    for (const auto& [code, count] : U.all()) {
        Count inA = A.get(code);
        if (inA < count) {
            R.m[code] = count - inA; // добавляем недостающую часть
        }
    }
    return R;
}


vector<pair<Code, Count>> MultiSet::dumpSorted() const{ // возврат отсортированного вектора
    vector<pair<Code, Count>> V(m.begin(), m.end());
    sort(V.begin(), V.end());
    return V;
}