#include "gray.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>

using namespace std;

GrayUniverse::GrayUniverse() : n(0) {}

unsigned long long GrayUniverse::grayInt(unsigned long long i) {
    return i ^ (i >> 1);
}

string GrayUniverse::toBinary(unsigned long long v, unsigned int length) {
    string s(length, '0');
    for (int i = length - 1; i >= 0; i--) {
        s[i] = (v & 1ull) ? '1' : '0';
        v >>= 1;
    }
    return s;
}

void GrayUniverse::generateAuto(unsigned int bits) {
    U.clear();
    n = bits;

    if (bits == 0){
    n = 0;
    U.clear();
    return;
    }

    size_t maxSize = 1ull << bits;
    vector<Code> grayCodes;
    grayCodes.reserve(maxSize);

    for (unsigned long long i = 0; i < maxSize; ++i) {
        grayCodes.push_back(toBinary(grayInt(i), bits));
    }

    random_device rb;
    mt19937 gen(rb());
    uniform_int_distribution<> dist(1, 50);

    for (const auto& code : grayCodes) {
        Count car = dist(gen);
        U[code] = car;
    }
}

const unordered_map<Code, Count>& GrayUniverse::all() const {
    return U;
}

bool GrayUniverse::contains(const Code& c) const {
    return U.find(c) != U.end();
}

size_t GrayUniverse::size() const {
    return U.size();
}

Count GrayUniverse::cardinality(const Code& c) const {
    auto it = U.find(c);
    return (it != U.end()) ? it->second : 0;
}

unsigned int GrayUniverse::bits() const {
    return n;
}

void GrayUniverse::printUniverse() const {
    if (U.empty()) {
        cout << "U = ∅\n";
        cout << "Мощность универсума: 0\n";
        return;
    }

    cout << "Универсум (n = " << n << ", size = " << U.size() << "):\n";
    size_t i = 1;
    for (const auto& [code, count] : U) {
        cout << i++ << ": " << code << " : " << count << "\n";
    }
}


Code GrayUniverse::atIndex(size_t i) const {
    if (i >= U.size()) throw std::out_of_range("Index out of range");
    auto it = U.begin();
    std::advance(it, i);
    return it->first; // возвращаем код
}
