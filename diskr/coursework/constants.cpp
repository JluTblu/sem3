#include "constants.h"

const std::vector<char> SYMBOLS = {'a', 'b', 'e', 'd', 'g', 'c', 'f', 'h'}; // Последовательность a -> b -> e -> d -> g -> c -> f -> h -> a
const int MOD = SYMBOLS.size();
const char ADDITIVE_UNIT = SYMBOLS[0]; // 'a' = 0
const char MULTIPLICATIVE_UNIT = SYMBOLS[1]; // 'b' = 1
const std::string INFINITY_INTERVAL_STR = "[-hhhhhhhh, hhhhhhhh]";
const std::string EMPTY_SET_STR = "{}";
const int MAX_DIGITS = 8;
