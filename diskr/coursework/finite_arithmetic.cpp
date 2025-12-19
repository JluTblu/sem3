#include "finite_arithmetic.h"
#include <algorithm>
#include <sstream>

const std::string FiniteArithmetic::ALPHABET = "abcdefgh";

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================================

char FiniteArithmetic::valueToChar(int value) const {
    return ALPHABET[value % BASE];
}

int FiniteArithmetic::charToValue(char c) const {
    for (int i = 0; i < BASE; ++i) {
        if (ALPHABET[i] == c) return i;
    }
    throw std::invalid_argument("Недопустимый символ: " + std::string(1, c));
}

bool FiniteArithmetic::isZero(const std::string& num) const {
    if (num.empty()) return true;
    for (char c : num) {
        if (c != ADDITIVE_IDENTITY) return false;
    }
    return true;
}

std::string FiniteArithmetic::removeLeadingZeros(const std::string& num) const {
    size_t pos = num.find_first_not_of(ADDITIVE_IDENTITY);
    if (pos == std::string::npos) {
        return std::string(1, ADDITIVE_IDENTITY);
    }
    return num.substr(pos);
}

int FiniteArithmetic::compareAbs(const std::string& num1, const std::string& num2) const {
    std::string n1 = removeLeadingZeros(num1);
    std::string n2 = removeLeadingZeros(num2);
    
    if (n1.length() != n2.length()) {
        return n1.length() > n2.length() ? 1 : -1;
    }
    
    if (n1 > n2) return 1;
    if (n1 < n2) return -1;
    return 0;
}

void FiniteArithmetic::validateNumber(const std::string& num) const {
    std::string cleanNum = num;
    if (!cleanNum.empty() && (cleanNum[0] == '-' || cleanNum[0] == '+')) {
        cleanNum = cleanNum.substr(1);
    }
    
    if (cleanNum.length() > MAX_LENGTH) {
        throw std::overflow_error("Число превышает " + std::to_string(MAX_LENGTH) + " разрядов");
    }
    
    for (char c : cleanNum) {
        if (ALPHABET.find(c) == std::string::npos) {
            throw std::invalid_argument("Недопустимый символ: " + std::string(1, c));
        }
    }
}

// ============================================================================
// БАЗОВЫЕ ОПЕРАЦИИ МАЛОЙ АРИФМЕТИКИ
// ============================================================================

std::string FiniteArithmetic::increment(const std::string& num) const {
    if (num.empty() || isZero(num)) {
        return std::string(1, MULTIPLICATIVE_IDENTITY);
    }
    
    std::string result = num;
    bool carry = true;
    
    for (int i = result.length() - 1; i >= 0 && carry; --i) {
        int val = charToValue(result[i]);
        val++;
        if (val >= BASE) {
            result[i] = ADDITIVE_IDENTITY;
            carry = true;
        } else {
            result[i] = valueToChar(val);
            carry = false;
        }
    }
    
    if (carry) {
        result = std::string(1, MULTIPLICATIVE_IDENTITY) + result;
    }
    
    return result;
}

std::string FiniteArithmetic::decrement(const std::string& num) const {
    if (num.empty() || num == std::string(1, MULTIPLICATIVE_IDENTITY)) {
        return std::string(1, ADDITIVE_IDENTITY);
    }
    
    std::string result = num;
    bool borrow = true;
    
    for (int i = result.length() - 1; i >= 0 && borrow; --i) {
        int val = charToValue(result[i]);
        if (val == 0) {
            result[i] = valueToChar(BASE - 1);
            borrow = true;
        } else {
            result[i] = valueToChar(val - 1);
            borrow = false;
        }
    }
    
    return removeLeadingZeros(result);
}

// ============================================================================
// ОПЕРАЦИИ С ПОЛОЖИТЕЛЬНЫМИ ЧИСЛАМИ
// ============================================================================

std::string FiniteArithmetic::addPositive(const std::string& num1, const std::string& num2) const {
    std::string result = num1;
    std::string counter(1, ADDITIVE_IDENTITY);
    
    // Сложение через последовательное прибавление единицы
    while (counter != num2) {
        result = increment(result);
        counter = increment(counter);
        
        if (result.length() > MAX_LENGTH) {
            throw std::overflow_error("Переполнение: результат превышает 8 разрядов");
        }
    }
    
    return result;
}

std::string FiniteArithmetic::subtractPositive(const std::string& num1, const std::string& num2) const {
    if (compareAbs(num1, num2) < 0) {
        throw std::invalid_argument("num1 должно быть >= num2");
    }
    
    std::string result = num1;
    std::string counter(1, ADDITIVE_IDENTITY);
    
    // Вычитание через последовательное вычитание единицы
    while (counter != num2) {
        result = decrement(result);
        counter = increment(counter);
    }
    
    return result;
}

std::string FiniteArithmetic::multiplyPositive(const std::string& num1, const std::string& num2) const {
    if (isZero(num1) || isZero(num2)) {
        return std::string(1, ADDITIVE_IDENTITY);
    }
    
    std::string result(1, ADDITIVE_IDENTITY);
    std::string counter(1, ADDITIVE_IDENTITY);
    
    // Умножение через последовательное сложение
    while (counter != num2) {
        result = addPositive(result, num1);
        counter = increment(counter);
        
        if (result.length() > MAX_LENGTH) {
            throw std::overflow_error("Переполнение: результат превышает 8 разрядов");
        }
    }
    
    return result;
}

std::pair<std::string, std::string> FiniteArithmetic::dividePositive(const std::string& num1, const std::string& num2) const {
    // Деление на ноль
    if (isZero(num2)) {
        if (isZero(num1)) {
            // 0/0 - диапазон всех чисел
            std::string maxNum(MAX_LENGTH, ALPHABET[BASE - 1]);
            return {std::string(1, ADDITIVE_IDENTITY), "[-" + maxNum + "; " + maxNum + "]"};
        } else {
            // n/0 = Ø
            return {std::string(1, ADDITIVE_IDENTITY), "Ø"};
        }
    }
    
    if (isZero(num1)) {
        return {std::string(1, ADDITIVE_IDENTITY), std::string(1, ADDITIVE_IDENTITY)};
    }
    
    std::string quotient(1, ADDITIVE_IDENTITY);
    std::string remainder = num1;
    
    // Деление через последовательное вычитание
    while (compareAbs(remainder, num2) >= 0) {
        remainder = subtractPositive(remainder, num2);
        quotient = increment(quotient);
    }
    
    return {quotient, remainder};
}

// ============================================================================
// ОСНОВНЫЕ АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ
// ============================================================================

std::string FiniteArithmetic::add(const std::string& num1, const std::string& num2) const {
    validateNumber(num1);
    validateNumber(num2);
    
    bool sign1 = !num1.empty() && num1[0] == '-';
    bool sign2 = !num2.empty() && num2[0] == '-';
    
    std::string n1 = sign1 ? num1.substr(1) : num1;
    std::string n2 = sign2 ? num2.substr(1) : num2;
    
    n1 = removeLeadingZeros(n1);
    n2 = removeLeadingZeros(n2);
    
    if (!sign1 && !sign2) {
        // Оба положительные
        std::string result = addPositive(n1, n2);
        return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : result;
    } else if (sign1 && sign2) {
        // Оба отрицательные
        std::string result = addPositive(n1, n2);
        return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : "-" + result;
    } else if (!sign1 && sign2) {
        // num1 - num2
        int cmp = compareAbs(n1, n2);
        if (cmp > 0) {
            std::string result = subtractPositive(n1, n2);
            return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : result;
        } else if (cmp < 0) {
            std::string result = subtractPositive(n2, n1);
            return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : "-" + result;
        } else {
            return std::string(1, ADDITIVE_IDENTITY);
        }
    } else {
        // -num1 + num2 = num2 - num1
        int cmp = compareAbs(n2, n1);
        if (cmp > 0) {
            std::string result = subtractPositive(n2, n1);
            return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : result;
        } else if (cmp < 0) {
            std::string result = subtractPositive(n1, n2);
            return isZero(result) ? std::string(1, ADDITIVE_IDENTITY) : "-" + result;
        } else {
            return std::string(1, ADDITIVE_IDENTITY);
        }
    }
}

std::string FiniteArithmetic::subtract(const std::string& num1, const std::string& num2) const {
    // num1 - num2 = num1 + (-num2)
    std::string negNum2;
    if (!num2.empty() && num2[0] == '-') {
        negNum2 = num2.substr(1);
    } else {
        negNum2 = "-" + num2;
    }
    return add(num1, negNum2);
}

std::string FiniteArithmetic::multiply(const std::string& num1, const std::string& num2) const {
    validateNumber(num1);
    validateNumber(num2);
    
    bool sign1 = !num1.empty() && num1[0] == '-';
    bool sign2 = !num2.empty() && num2[0] == '-';
    
    std::string n1 = sign1 ? num1.substr(1) : num1;
    std::string n2 = sign2 ? num2.substr(1) : num2;
    
    n1 = removeLeadingZeros(n1);
    n2 = removeLeadingZeros(n2);
    
    std::string result = multiplyPositive(n1, n2);
    
    if (isZero(result)) {
        return std::string(1, ADDITIVE_IDENTITY);
    }
    
    // Определяем знак: разные знаки = отрицательный результат
    if (sign1 != sign2) {
        return "-" + result;
    }
    
    return result;
}

std::string FiniteArithmetic::divide(const std::string& num1, const std::string& num2) const {
    validateNumber(num1);
    validateNumber(num2);
    
    bool sign1 = !num1.empty() && num1[0] == '-';
    bool sign2 = !num2.empty() && num2[0] == '-';
    
    std::string n1 = sign1 ? num1.substr(1) : num1;
    std::string n2 = sign2 ? num2.substr(1) : num2;
    
    n1 = removeLeadingZeros(n1);
    n2 = removeLeadingZeros(n2);
    
    auto [quotient, remainder] = dividePositive(n1, n2);
    
    // Обработка специальных случаев (Ø и диапазон)
    if (remainder == "Ø" || remainder.find('[') != std::string::npos) {
        return remainder;
    }
    
    // Деление отрицательного на положительное
    if (sign1 && !sign2) {
        if (!isZero(remainder)) {
            // -7/3 = -3(2), а не -2(1)
            quotient = increment(quotient);
            remainder = subtractPositive(n2, remainder);
        }
        std::string qSign = isZero(quotient) ? "" : "-";
        return qSign + quotient + "(" + remainder + ")";
    }
    
    // Деление положительного на отрицательное
    if (!sign1 && sign2) {
        std::string qSign = isZero(quotient) ? "" : "-";
        return qSign + quotient + "(" + remainder + ")";
    }
    
    // Деление двух отрицательных или двух положительных
    return quotient + "(" + remainder + ")";
}
