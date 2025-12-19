#ifndef BIGFINITENUMBER_H
#define BIGFINITENUMBER_H

#include <string>
#include <utility>
#include <iostream>

class BigFiniteNumber {
private:
    std::string value;
    bool is_negative;
    
    std::string normalize(std::string num_str) const;
    std::string pad_left(std::string num_str, int target_len) const;
    void check_overflow() const;
    int compare_abs(const BigFiniteNumber& other) const;
    
    BigFiniteNumber(std::string val, bool neg);
    
public:
    BigFiniteNumber();
    BigFiniteNumber(const std::string& num_str);
    
    static BigFiniteNumber from_internal_string(const std::string& val, bool neg);
    
    friend std::ostream& operator<<(std::ostream& os, const BigFiniteNumber& num);
    
    bool operator==(const BigFiniteNumber& other) const;
    bool operator!=(const BigFiniteNumber& other) const;
    bool operator<(const BigFiniteNumber& other) const;
    bool operator>(const BigFiniteNumber& other) const;
    bool operator<=(const BigFiniteNumber& other) const;
    bool operator>=(const BigFiniteNumber& other) const;
    
    BigFiniteNumber operator+(const BigFiniteNumber& other) const;
    BigFiniteNumber operator-(const BigFiniteNumber& other) const;
    BigFiniteNumber operator*(const BigFiniteNumber& other) const;
    std::pair<BigFiniteNumber, BigFiniteNumber> divide(const BigFiniteNumber& other) const;
    
    // Дополнительные операции
    BigFiniteNumber power(const BigFiniteNumber& exp) const;
    static BigFiniteNumber gcd(const BigFiniteNumber& a, const BigFiniteNumber& b);
    static BigFiniteNumber lcm(const BigFiniteNumber& a, const BigFiniteNumber& b);
    
    std::string get_value() const { return value; }
    bool get_is_negative() const { return is_negative; }
};

#endif // BIGFINITENUMBER_H
