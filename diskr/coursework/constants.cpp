#include "constants.h"

// Вариант 48: Z₈, b, e, f, g, d, h, c, a
// Правило "+1": a->b, b->e, c->f, d->g, e->d, f->h, g->c, h->a
// Последовательность в цикле: a -> b -> e -> d -> g -> c -> f -> h -> a
const std::vector<char> SYMBOLS = {'a', 'b', 'e', 'd', 'g', 'c', 'f', 'h'};
const int MOD = SYMBOLS.size();
const char ADDITIVE_UNIT = SYMBOLS[0];      // 'a' = 0
const char MULTIPLICATIVE_UNIT = SYMBOLS[1]; // 'b' = 1
const std::string INFINITY_INTERVAL_STR = "[-hhhhhhhh, hhhhhhhh]";
const std::string EMPTY_SET_STR = "{}";
const int MAX_DIGITS = 8;
