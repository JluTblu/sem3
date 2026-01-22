#include "utils.h"
#include "constants.h"
#include <iostream>

std::map<char, char> NEXT_SYMBOL_MAP;
std::map<char, char> SYMBOL_NEGATION_MAP;
std::map<std::tuple<char, char, char>, std::pair<char, char>> ADDITION_TABLE;

char symbolic_add_simple(char digit1, char digit2) {
    if (digit1 == get_additive_unit()) return digit2;
    if (digit2 == get_additive_unit()) return digit1;
    
    char sum_val = digit1;
    char counter = get_additive_unit();
    
    while (counter != digit2) {
        sum_val = NEXT_SYMBOL_MAP.at(sum_val);
        counter = NEXT_SYMBOL_MAP.at(counter);
    }
    
    return sum_val;
}

void init_symbols_maps() {
    NEXT_SYMBOL_MAP['a'] = 'b';
    NEXT_SYMBOL_MAP['b'] = 'e';
    NEXT_SYMBOL_MAP['e'] = 'd';
    NEXT_SYMBOL_MAP['d'] = 'g';
    NEXT_SYMBOL_MAP['g'] = 'c';
    NEXT_SYMBOL_MAP['c'] = 'f';
    NEXT_SYMBOL_MAP['f'] = 'h';
    NEXT_SYMBOL_MAP['h'] = 'a';
    
    // Построение таблицы отрицаний
    for (char symbol : SYMBOLS) {
        char probe = symbol;
        char inverse = get_additive_unit();
        
        while (probe != get_additive_unit()) {
            probe = NEXT_SYMBOL_MAP.at(probe);
            inverse = NEXT_SYMBOL_MAP.at(inverse);
        }
        
        SYMBOL_NEGATION_MAP[symbol] = inverse;
    }
    
    SYMBOL_NEGATION_MAP['a'] = 'a';
    
    for (char operand1 : SYMBOLS){
        for (char operand2 : SYMBOLS){
            for (char input_carry : SYMBOLS){
                
                // Сначала складываем operand1 + operand2
                char intermediate = symbolic_add_simple(operand1, operand2);
                
                // Проверяем overflow при первом сложении
                bool first_overflow = false;
                if (operand1 != get_additive_unit() && operand2 != get_additive_unit()) {
                    // Проверяем, прошли ли через 'a' во время сложения
                    char tracker = operand1;
                    char counter = get_additive_unit();
                    
                    while (counter != operand2) {
                        char prev = tracker;
                        tracker = NEXT_SYMBOL_MAP.at(tracker);
                        counter = NEXT_SYMBOL_MAP.at(counter);
                        
                        // Если tracker стал 'a', но мы еще не закончили - было переполнение
                        if (tracker == get_additive_unit() && counter != operand2) {
                            first_overflow = true;
                            break;
                        }
                    }
                }
                
                // Теперь добавляем input_carry к intermediate
                char final_result = symbolic_add_simple(intermediate, input_carry);
                
                // Проверяем overflow при втором сложении
                bool second_overflow = false;
                if (intermediate != get_additive_unit() && input_carry != get_additive_unit()) {
                    char tracker = intermediate;
                    char counter = get_additive_unit();
                    
                    while (counter != input_carry) {
                        char prev = tracker;
                        tracker = NEXT_SYMBOL_MAP.at(tracker);
                        counter = NEXT_SYMBOL_MAP.at(counter);
                        
                        // Если tracker стал 'a', но мы еще не закончили - было переполнение
                        if (tracker == get_additive_unit() && counter != input_carry) {
                            second_overflow = true;
                            break;
                        }
                    }
                }
                
                // Определяем выходной перенос
                char output_carry = get_additive_unit();
                if (first_overflow || second_overflow) {
                    output_carry = get_multiplicative_unit();
                }
                
                ADDITION_TABLE[std::make_tuple(operand1, operand2, input_carry)] = 
                    std::make_pair(final_result, output_carry);
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
    
    char position = get_additive_unit();
    while (true){
        if (position == c1) return -1;
        if (position == c2) return 1;
        position = NEXT_SYMBOL_MAP.at(position);
        if (position == get_additive_unit()) break;
    }
    return 0;
}