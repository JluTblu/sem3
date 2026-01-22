#include "arithmetic.h"
#include "utils.h"
#include "constants.h"

char next_symbol(char currentChar){
    if (!is_valid_digit(currentChar)){
        throw std::logic_error("error");
    }
    return NEXT_SYMBOL_MAP.at(currentChar);
}

char prev_symbol(char currentChar){
    if (!is_valid_digit(currentChar)){
        throw std::logic_error("error");
    }
    char current = get_additive_unit();
    char prev = get_additive_unit();
    
    while (current != currentChar){
        prev = current;
        current = next_symbol(current);
    }
    return prev;
}

char symbolic_add(char operand1, char operand2){
    if (!is_valid_digit(operand1) || !is_valid_digit(operand2)){
        throw std::logic_error("error");
    }
    auto [sum, carry] = ADDITION_TABLE[std::make_tuple(operand1, operand2, get_additive_unit())];
    return sum;
}

char symbolic_negate(char c){
    if (!is_valid_digit(c)){
        throw std::logic_error("error");
    }
    return SYMBOL_NEGATION_MAP.at(c);
}

char symbolic_multiply(char operand1, char operand2){
    if (!is_valid_digit(operand1) || !is_valid_digit(operand2)){
        throw std::logic_error("error");
    }
    if (operand1 == get_additive_unit() || operand2 == get_additive_unit()){
        return get_additive_unit();
    }
    if (operand1 == get_multiplicative_unit()) return operand2;
    if (operand2 == get_multiplicative_unit()) return operand1;
    
    char res = get_additive_unit();
    char counter = get_additive_unit();
    while (counter != operand2){
        res = symbolic_add(res, operand1);
        counter = next_symbol(counter);
    }
    return res;
}
