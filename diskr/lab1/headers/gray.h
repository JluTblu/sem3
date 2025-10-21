#ifndef GRAY_H
#define GRAY_H

#include <string>
#include <unordered_map>

// Определяем типы Code и Count
using Code = std::string;
using Count = unsigned int;

class GrayUniverse{
private:
    unsigned int n;
    std::unordered_map<Code, Count> U; // теперь храним коды с кратностями

public:
    GrayUniverse(); // Конструктор

    void generateAuto(unsigned int bits); // только эта функция задаёт универсум

    const std::unordered_map<Code, Count>& all() const;
    bool contains(const Code& c) const;
    size_t size() const;
    Code atIndex(size_t i) const;
    Count cardinality(const Code& c) const;
    unsigned int bits() const;
    void printUniverse() const;

private:
    static unsigned long long grayInt(unsigned long long i);
    static std::string toBinary(unsigned long long v, unsigned int length);
};

#endif
