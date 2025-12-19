#include "utils.h"
#include "constants.h"
#include <iostream>

std::map<char, char> NEXT_SYMBOL_MAP;
std::map<char, char> SYMBOL_NEGATION_MAP;
std::map<std::tuple<char, char, char>, std::pair<char, char>> ADDITION_TABLE;

char symbolic_add_simple(char char1, char char2) {
    if (char1 == get_additive_unit()) return char2;
    if (char2 == get_additive_unit()) return char1;
    
    char result = char1;
    char counter = get_additive_unit();
    
    while (counter != char2) {
        result = NEXT_SYMBOL_MAP.at(result);
        counter = NEXT_SYMBOL_MAP.at(counter);
    }
    
    return result;
}

void init_symbols_maps() {
    // Вариант 48: правило "+1" из таблицы
    // Строка 48: Z₈, b, e, f, g, d, h, c, a
    // a+1=b, b+1=e, c+1=f, d+1=g, e+1=d, f+1=h, g+1=c, h+1=a
    
    NEXT_SYMBOL_MAP['a'] = 'b';
    NEXT_SYMBOL_MAP['b'] = 'e';
    NEXT_SYMBOL_MAP['c'] = 'f';
    NEXT_SYMBOL_MAP['d'] = 'g';
    NEXT_SYMBOL_MAP['e'] = 'd';
    NEXT_SYMBOL_MAP['f'] = 'h';
    NEXT_SYMBOL_MAP['g'] = 'c';
    NEXT_SYMBOL_MAP['h'] = 'a';  // Переполнение!
    
    // Таблица отрицаний: находим такое x, что y + x = a (mod 8)
    // Для каждого символа находим его противоположность
    for (char c : SYMBOLS) {
        char current = c;
        char counter = get_additive_unit();
        
        // Ищем, сколько раз нужно прибавить 1 к c, чтобы получить 'a'
        while (current != get_additive_unit()) {
            current = NEXT_SYMBOL_MAP.at(current);
            counter = NEXT_SYMBOL_MAP.at(counter);
        }
        
        SYMBOL_NEGATION_MAP[c] = counter;
    }
    
    // Специальные случаи (проверка)
    SYMBOL_NEGATION_MAP['a'] = 'a'; // 0 + 0 = 0
    
    // Таблица сложения с переносом
    for (char c1 : SYMBOLS) {
        for (char c2 : SYMBOLS) {
            for (char carry_in : SYMBOLS) {
                // Складываем c1 + c2 + carry_in пошагово
                char result = c1;
                int steps = 0;
                
                // Прибавляем c2
                char temp_c2 = get_additive_unit();
                while (temp_c2 != c2) {
                    char prev_result = result;
                    result = NEXT_SYMBOL_MAP.at(result);
                    temp_c2 = NEXT_SYMBOL_MAP.at(temp_c2);
                    steps++;
                    
                    // Переполнение: result стал меньше prev_result
                    if (result == get_additive_unit()) {
                        steps = MOD + steps;
                    }
                }
                
                // Прибавляем carry_in
                char temp_carry = get_additive_unit();
                while (temp_carry != carry_in) {
                    char prev_result = result;
                    result = NEXT_SYMBOL_MAP.at(result);
                    temp_carry = NEXT_SYMBOL_MAP.at(temp_carry);
                    steps++;
                    
                    // Переполнение
                    if (result == get_additive_unit() && temp_carry != carry_in) {
                        steps = MOD + steps;
                    }
                }
                
                // Определяем carry_out
                char carry_out = get_additive_unit();
                if (steps >= MOD) {
                    carry_out = get_multiplicative_unit();
                }
                
                ADDITION_TABLE[std::make_tuple(c1, c2, carry_in)] = std::make_pair(result, carry_out);
            }
        }
    }
}

bool is_valid_digit(char c) {
    return NEXT_SYMBOL_MAP.count(c);
}

char get_additive_unit() {
    return 'a';
}

char get_multiplicative_unit() {
    return 'b';
}

std::string get_min_value_str() {
    // Максимальное отрицательное число
    return "-" + std::string(MAX_DIGITS, 'h');
}

std::string get_max_value_str() {
    // Максимальное положительное число
    return std::string(MAX_DIGITS, 'h');
}

int compare_chars(char c1, char c2) {
    if (c1 == c2) return 0;
    
    char current = get_additive_unit();
    while (true) {
        if (current == c1) return -1;
        if (current == c2) return 1;
        current = NEXT_SYMBOL_MAP.at(current);
        if (current == get_additive_unit()) break;
    }
    return 0;
}
