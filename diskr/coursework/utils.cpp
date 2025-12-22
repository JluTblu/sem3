#include "utils.h"
#include "constants.h"
#include <iostream>

std::map<char, char> NEXT_SYMBOL_MAP;
std::map<char, char> SYMBOL_NEGATION_MAP;
std::map<std::tuple<char, char, char>, std::pair<char, char>> ADDITION_TABLE;

char symbolic_add_simple(char char1, char char2){
    if (char1 == get_additive_unit()) return char2;
    if (char2 == get_additive_unit()) return char1;
    
    char result = char1;
    char counter = get_additive_unit();
    
    while (counter != char2){
        result = NEXT_SYMBOL_MAP.at(result);
        counter = NEXT_SYMBOL_MAP.at(counter);
    }
    
    return result;
}

void init_symbols_maps(){ // a+1=b, b+1=e, c+1=f, d+1=g, e+1=d, f+1=h, g+1=c, h+1=a
    
    NEXT_SYMBOL_MAP['a'] = 'b';
    NEXT_SYMBOL_MAP['b'] = 'e';
    NEXT_SYMBOL_MAP['c'] = 'f';
    NEXT_SYMBOL_MAP['d'] = 'g';
    NEXT_SYMBOL_MAP['e'] = 'd';
    NEXT_SYMBOL_MAP['f'] = 'h';
    NEXT_SYMBOL_MAP['g'] = 'c';
    NEXT_SYMBOL_MAP['h'] = 'a';// Переполнение
    
    //  находим такое x, что y + x = a, для каждого символа находим его противоположность
    for (char c : SYMBOLS){
        char current = c;
        char counter = get_additive_unit();
        
        while (current != get_additive_unit()){ // ищем, сколько раз нужно прибавить 1 к c, чтобы получить 'a'
            current = NEXT_SYMBOL_MAP.at(current);
            counter = NEXT_SYMBOL_MAP.at(counter);
        }
        SYMBOL_NEGATION_MAP[c] = counter;
    }
    
    SYMBOL_NEGATION_MAP['a'] = 'a'; // 0 + 0 = 0
    
    for (char c1 : SYMBOLS){
        for (char c2 : SYMBOLS){ // складываем c1 + c2 + carry_in пошагово
            for (char carry_in : SYMBOLS){
                char result = c1;
                int steps = 0;
                
                char temp_c2 = get_additive_unit(); // с с2 работаем
                while (temp_c2 != c2){ //прибавить к c1 единицу столько раз, сколько единиц в c2
                    char prev_result = result;
                    result = NEXT_SYMBOL_MAP.at(result);
                    temp_c2 = NEXT_SYMBOL_MAP.at(temp_c2);
                    steps++;
                    
                    if (result == get_additive_unit()){ // переполнение- result стал меньше prev_result
                        steps = MOD + steps;
                    }
                }
                
                char temp_carry = get_additive_unit(); // а тут уже с переносом
                while (temp_carry != carry_in){
                    char prev_result = result;
                    result = NEXT_SYMBOL_MAP.at(result);
                    temp_carry = NEXT_SYMBOL_MAP.at(temp_carry);
                    steps++;
                    
                    if (result == get_additive_unit() && temp_carry != carry_in){ // переполнение
                        steps = MOD + steps; // если мы уже остановились на "a", но при этом еще не закончили с переносом
                    }
                }
                
                char carry_out = get_additive_unit(); // результат сложения текущего разряда, который нужно передать следующему разряду
                if (steps >= MOD){
                    carry_out = get_multiplicative_unit();
                }
                
                ADDITION_TABLE[std::make_tuple(c1, c2, carry_in)] = std::make_pair(result, carry_out);
            }
        }
    }
}

bool is_valid_digit(char c){
    return NEXT_SYMBOL_MAP.count(c);
}

char get_additive_unit(){
    return 'a';
}

char get_multiplicative_unit(){
    return 'b';
}

std::string get_min_value_str(){
    // Максимальное отрицательное число
    return "-" + std::string(MAX_DIGITS, 'h');
}

std::string get_max_value_str(){
    // Максимальное положительное число
    return std::string(MAX_DIGITS, 'h');
}

int compare_chars(char c1, char c2){
    if (c1 == c2) return 0;
    
    char current = get_additive_unit();
    while (true){
        if (current == c1) return -1;
        if (current == c2) return 1;
        current = NEXT_SYMBOL_MAP.at(current);
        if (current == get_additive_unit()) break;
    }
    return 0;
}
