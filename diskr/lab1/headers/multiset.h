#ifndef MULTISET_H
#define MULTISET_H

#include "gray.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class MultiSet {
private:
    unordered_map<Code, Count> m;

public:
    MultiSet(); // Конструктор
    void clear();
    bool empty() const;
    void add(const GrayUniverse& U, const Code& c, Count k);
    Count get(const Code& c) const;
    void print(const string& title = "") const;
    MultiSet set_union(const MultiSet& B) const; // объединение
    MultiSet set_inter(const MultiSet& B) const; // пересечение
    MultiSet set_diff(const MultiSet& B) const; // разность
    MultiSet set_symdiff(const MultiSet& B) const; // симметрическая разность
    MultiSet add(const MultiSet& B) const; // поэлементная сумма
    MultiSet sub(const MultiSet& B) const;// поэлементная разность
    MultiSet mul(const MultiSet& B) const;// поэлементное умножение
    MultiSet div(const MultiSet& B) const;// поэлементное деление
    static MultiSet complement(const GrayUniverse& U, const MultiSet& A); // дополнение
    vector<pair<Code, Count>> dumpSorted() const; // возвращаем отсортированный вектор пар код наш и кратность
};

#endif // MULTISET_H