#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

// Вариант 48: последовательность для правила "+1"
// a -> b -> e -> d -> g -> c -> f -> h -> a (цикл)
extern const std::vector<char> SYMBOLS;
extern const int MOD;
extern const char ADDITIVE_UNIT;
extern const char MULTIPLICATIVE_UNIT;
extern const std::string INFINITY_INTERVAL_STR;
extern const std::string EMPTY_SET_STR;
extern const int MAX_DIGITS;

#endif // CONSTANTS_H
