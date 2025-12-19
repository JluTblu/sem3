#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <tuple>
#include <utility>
#include <string>

// Таблица переходов для правила "+1"
extern std::map<char, char> NEXT_SYMBOL_MAP;

// Таблица отрицаний (для вычитания)
extern std::map<char, char> SYMBOL_NEGATION_MAP;

// Таблица сложения с переносом: (digit1, digit2, carry_in) -> (sum, carry_out)
extern std::map<std::tuple<char, char, char>, std::pair<char, char>> ADDITION_TABLE;

// Инициализация всех таблиц
void init_symbols_maps();

// Проверка валидности символа
bool is_valid_digit(char c);

// Получение единиц
char get_additive_unit();
char get_multiplicative_unit();

// Получение минимального и максимального значений
std::string get_min_value_str();
std::string get_max_value_str();

// Сравнение символов по их позиции в последовательности
int compare_chars(char c1, char c2);

#endif // UTILS_H
