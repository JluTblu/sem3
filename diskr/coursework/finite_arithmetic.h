#ifndef FINITE_ARITHMETIC_H
#define FINITE_ARITHMETIC_H

#include <string>
#include <stdexcept>

/**
 * Калькулятор конечной арифметики (вариант 48)
 * Система: Z₈ = {a, b, c, d, e, f, g, h}
 * Аддитивная единица: a (0)
 * Мультипликативная единица: b (1)
 * Максимальная длина: 8 разрядов
 */
class FiniteArithmetic {
private:
    static const int BASE = 8;           // Основание системы Z₈
    static const int MAX_LENGTH = 8;     // Максимальная длина числа
    static const char ADDITIVE_IDENTITY = 'a';  // Аддитивная единица (0)
    static const char MULTIPLICATIVE_IDENTITY = 'b';  // Мультипликативная единица (1)
    
    // Алфавит системы счисления
    static const std::string ALPHABET;
    
    // Вспомогательные функции
    char valueToChar(int value) const;
    int charToValue(char c) const;
    bool isZero(const std::string& num) const;
    int compareAbs(const std::string& num1, const std::string& num2) const;
    std::string removeLeadingZeros(const std::string& num) const;
    void validateNumber(const std::string& num) const;
    
    // Базовые операции малой арифметики
    std::string increment(const std::string& num) const;
    std::string decrement(const std::string& num) const;
    
    // Операции с положительными числами
    std::string addPositive(const std::string& num1, const std::string& num2) const;
    std::string subtractPositive(const std::string& num1, const std::string& num2) const;
    std::string multiplyPositive(const std::string& num1, const std::string& num2) const;
    std::pair<std::string, std::string> dividePositive(const std::string& num1, const std::string& num2) const;
    
public:
    // Основные арифметические операции
    std::string add(const std::string& num1, const std::string& num2) const;
    std::string subtract(const std::string& num1, const std::string& num2) const;
    std::string multiply(const std::string& num1, const std::string& num2) const;
    std::string divide(const std::string& num1, const std::string& num2) const;
    
    // Геттеры для констант
    static int getBase() { return BASE; }
    static int getMaxLength() { return MAX_LENGTH; }
    static char getAdditiveIdentity() { return ADDITIVE_IDENTITY; }
    static char getMultiplicativeIdentity() { return MULTIPLICATIVE_IDENTITY; }
    static std::string getAlphabet() { return ALPHABET; }
};

#endif // FINITE_ARITHMETIC_H
