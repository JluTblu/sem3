#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdexcept>

// Операции над символами
char next_symbol(char current_char);
char prev_symbol(char current_char);
char symbolic_add(char char1, char char2);
char symbolic_negate(char c);
char symbolic_multiply(char char1, char char2);

#endif // ARITHMETIC_H
