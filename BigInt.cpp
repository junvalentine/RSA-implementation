/*
    Adapted from https://github.com/faheel/BigInt    
*/
#include <string>

#include "Utils.h"
#include "BigInt.h"

/* Constructor */

// Default constructor
BigInt::BigInt() {
    value = "0";
    sign = '+';
}

// Copy constructor
BigInt::BigInt(const BigInt& num) {
    value = num.value;
    sign = num.sign;
}

// String to BigInt
BigInt::BigInt(const std::string& num) {
    if (num[0] == '+' or num[0] == '-') {     // check for sign
        std::string magnitude = num.substr(1);
        if (is_valid_number(magnitude)) {
            value = magnitude;
            sign = num[0];
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    else {      // if no sign is specified
        if (is_valid_number(num)) {
            value = num;
            sign = '+';    // positive by default
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    strip_leading_zeroes(value);
}

/* Operators */
// Assignment operator for BigInt
BigInt& BigInt::operator=(const BigInt& num) {
    value = num.value;
    sign = num.sign;

    return *this;
}

// Unary arithmetic operator +
BigInt BigInt::operator+() const {
    return *this;
}

// Unary arithmetic operator -
BigInt BigInt::operator-() const {
    BigInt temp;

    temp.value = value;
    if (value != "0") {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }

    return temp;
}

// Binary arithmetic operator +
BigInt BigInt::operator+(const BigInt& num) const {
    // if the operands are of opposite signs, perform subtraction
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this - rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs - num);
    }

    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

    BigInt result;      // the resultant sum
    result.value = "";  // the value is cleared as the digits will be appended
    short carry = 0, sum;
    // add the two values
    for (long i = larger.size() - 1; i >= 0; i--) {
        sum = larger[i] - '0' + smaller[i] - '0' + carry;
        result.value = std::to_string(sum % 10) + result.value;
        carry = sum / (short) 10;
    }
    if (carry)
        result.value = std::to_string(carry) + result.value;

    // if the operands are negative, the result is negative
    if (this->sign == '-' and result.value != "0")
        result.sign = '-';

    return result;
}

// Binary arithmetic operator -
BigInt BigInt::operator-(const BigInt& num) const {
    // if the operands are of opposite signs, perform addition
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this + rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs + num);
    }

    BigInt result;      // the resultant difference
    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    if (abs(*this) > abs(num)) {
        larger = this->value;
        smaller = num.value;

        if (this->sign == '-')      // -larger - -smaller = -result
            result.sign = '-';
    }
    else {
        larger = num.value;
        smaller = this->value;

        if (num.sign == '+')        // smaller - larger = -result
            result.sign = '-';
    }
    // pad the smaller number with zeroes
    add_leading_zeroes(smaller, larger.size() - smaller.size());

    result.value = "";  // the value is cleared as the digits will be appended
    short difference;
    long i, j;
    // subtract the two values
    for (i = larger.size() - 1; i >= 0; i--) {
        difference = larger[i] - smaller[i];
        if (difference < 0) {
            for (j = i - 1; j >= 0; j--) {
                if (larger[j] != '0') {
                    larger[j]--;    // borrow from the j-th digit
                    break;
                }
            }
            j++;
            while (j != i) {
                larger[j] = '9';    // add the borrow and take away 1
                j++;
            }
            difference += 10;   // add the borrow
        }
        result.value = std::to_string(difference) + result.value;
    }
    strip_leading_zeroes(result.value);

    // if the result is 0, set its sign as +
    if (result.value == "0")
        result.sign = '+';

    return result;
}

// Binary arithmetic operator *
BigInt BigInt::operator*(const BigInt& num) const {
    if (*this == 0 or num == 0)
        return BigInt(0);
    if (*this == 1)
        return num;
    if (num == 1)
     return *this;

    BigInt product;
    if (abs(*this) <= FLOOR_SQRT_LLONG_MAX and abs(num) <= FLOOR_SQRT_LLONG_MAX)
        product = std::stoll(this->value) * std::stoll(num.value);
    else if (is_power_of_10(this->value)){ // if LHS is a power of 10 do optimised operation 
        product.value = num.value;
        product.value.append(this->value.begin() + 1, this->value.end());
    }
    else if (is_power_of_10(num.value)){ // if RHS is a power of 10 do optimised operation 
        product.value = this->value;
        product.value.append(num.value.begin() + 1, num.value.end());
    }
    else {
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

        size_t half_length = larger.size() / 2;
        auto half_length_ceil = (size_t) ceil(larger.size() / 2.0);

        BigInt num1_high, num1_low;
        num1_high = larger.substr(0, half_length);
        num1_low = larger.substr(half_length);

        BigInt num2_high, num2_low;
        num2_high = smaller.substr(0, half_length);
        num2_low = smaller.substr(half_length);

        strip_leading_zeroes(num1_high.value);
        strip_leading_zeroes(num1_low.value);
        strip_leading_zeroes(num2_high.value);
        strip_leading_zeroes(num2_low.value);

        BigInt prod_high, prod_mid, prod_low;
        prod_high = num1_high * num2_high;
        prod_low = num1_low * num2_low;
        prod_mid = (num1_high + num1_low) * (num2_high + num2_low)
                   - prod_high - prod_low;

        add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
        add_trailing_zeroes(prod_mid.value, half_length_ceil);

        strip_leading_zeroes(prod_high.value);
        strip_leading_zeroes(prod_mid.value);
        strip_leading_zeroes(prod_low.value);

        product = prod_high + prod_mid + prod_low;
    }
    strip_leading_zeroes(product.value);

    if (this->sign == num.sign)
        product.sign = '+';
    else
        product.sign = '-';

    return product;
}

// Helper function
std::tuple<BigInt, BigInt> divide(const BigInt& dividend, const BigInt& divisor) {
    BigInt quotient, remainder, temp;

    temp = divisor;
    quotient = 1;
    while (temp < dividend) {
        quotient++;
        temp += divisor;
    }
    if (temp > dividend) {
        quotient--;
        remainder = dividend - (temp - divisor);
    }

    return std::make_tuple(quotient, remainder);
}

// Binary arithmetic operator /
BigInt BigInt::operator/(const BigInt& num) const {
    BigInt abs_dividend = abs(*this);
    BigInt abs_divisor = abs(num);

    if (num == 0)
        throw std::logic_error("Attempted division by zero");
    if (abs_dividend < abs_divisor)
        return BigInt(0);
    if (num == 1)
        return *this;
    if (num == -1)
        return -(*this);

    BigInt quotient;
    if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
        quotient = std::stoll(abs_dividend.value) / std::stoll(abs_divisor.value);
    else if (abs_dividend == abs_divisor)
        quotient = 1;
    else if (is_power_of_10(abs_divisor.value)) { // if divisor is a power of 10 do optimised calculation
        size_t digits_in_quotient = abs_dividend.value.size() - abs_divisor.value.size() + 1;
        quotient.value = abs_dividend.value.substr(0, digits_in_quotient);
    }
    else {
        quotient.value = "";    // the value is cleared as digits will be appended
        BigInt chunk, chunk_quotient, chunk_remainder;
        size_t chunk_index = 0;
        chunk_remainder.value = abs_dividend.value.substr(chunk_index, abs_divisor.value.size() - 1);
        chunk_index = abs_divisor.value.size() - 1;
        while (chunk_index < abs_dividend.value.size()) {
            chunk.value = chunk_remainder.value.append(1, abs_dividend.value[chunk_index]);
            chunk_index++;
            while (chunk < abs_divisor) {
                quotient.value += "0";
                if (chunk_index < abs_dividend.value.size()) {
                    chunk.value.append(1, abs_dividend.value[chunk_index]);
                    chunk_index++;
                }
                else
                    break;
            }
            if (chunk == abs_divisor) {
                quotient.value += "1";
                chunk_remainder = 0;
            }
            else if (chunk > abs_divisor) {
                strip_leading_zeroes(chunk.value);
                std::tie(chunk_quotient, chunk_remainder) = divide(chunk, abs_divisor);
                quotient.value += chunk_quotient.value;
            }
        }
    }
    strip_leading_zeroes(quotient.value);

    if (this->sign == num.sign)
        quotient.sign = '+';
    else
        quotient.sign = '-';

    return quotient;
}

// Binary arithmetic operator %
BigInt BigInt::operator%(const BigInt& num) const {
    BigInt abs_dividend = abs(*this);
    BigInt abs_divisor = abs(num);

    if (abs_divisor == 0)
        throw std::logic_error("Attempted division by zero");
    if (abs_divisor == 1 or abs_divisor == abs_dividend)
        return BigInt(0);

    BigInt remainder;
    if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
        remainder = std::stoll(abs_dividend.value) % std::stoll(abs_divisor.value);
    else if (abs_dividend < abs_divisor)
        remainder = abs_dividend;
    else if (is_power_of_10(num.value)){ // if num is a power of 10 use optimised calculation
        size_t no_of_zeroes = num.value.size() - 1;
        remainder.value = abs_dividend.value.substr(abs_dividend.value.size() - no_of_zeroes);
    } 
    else {
        BigInt quotient = abs_dividend / abs_divisor;
        remainder = abs_dividend - quotient * abs_divisor;
    }
    strip_leading_zeroes(remainder.value);

    // remainder has the same sign as that of the dividend
    remainder.sign = this->sign;
    if (remainder.value == "0")     // except if its zero
        remainder.sign = '+';

    return remainder;
}

// Arithmetic-assignment operator +=
BigInt& BigInt::operator+=(const BigInt& num) {
    *this = *this + num;

    return *this;
}

// Arithmetic-assignment operator -=
BigInt& BigInt::operator-=(const BigInt& num) {
    *this = *this - num;

    return *this;
}


// Arithmetic-assignment operator *=
BigInt& BigInt::operator*=(const BigInt& num) {
    *this = *this * num;

    return *this;
}

// Arithmetic-assignment operator /=
BigInt& BigInt::operator/=(const BigInt& num) {
    *this = *this / num;

    return *this;
}

// Arithmetic-assignment operator %=
BigInt& BigInt::operator%=(const BigInt& num) {
    *this = *this % num;

    return *this;
}

// Pre-increment
BigInt& BigInt::operator++() {
    *this += 1;

    return *this;
}

// Pre-decrement
BigInt& BigInt::operator--() {
    *this -= 1;

    return *this;
}


// Post-increment
BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this += 1;

    return temp;
}

// Post-decrement
BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    *this -= 1;

    return temp;
}

// Relational operators ==
bool BigInt::operator==(const BigInt& num) const {
    return (sign == num.sign) and (value == num.value);
}

// Relational operators !=
bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}

// Relational operators <
bool BigInt::operator<(const BigInt& num) const {
    if (sign == num.sign) {
        if (sign == '+') {
            if (value.length() == num.value.length())
                return value < num.value;
            else
                return value.length() < num.value.length();
        }
        else
            return -(*this) > -num;
    }
    else
        return sign == '-';
}

// Relational operators >
bool BigInt::operator>(const BigInt& num) const {
    return !((*this < num) or (*this == num));
}

// Relational operators <=
bool BigInt::operator<=(const BigInt& num) const {
    return (*this < num) or (*this == num);
}

// Relational operators >=
bool BigInt::operator>=(const BigInt& num) const {
    return !(*this < num);
}

// I/O stream operators (input)
std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);  // remove sign from value and set sign, if exists

    return in;
}

// I/O stream operators (output)
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;

    return out;
}

/* Conversion */

// Converts a BigInt to a string.
std::string BigInt::to_string() const {
    // prefix with sign if negative
    return this->sign == '-' ? "-" + this->value : this->value;
}

/* Math */

// Returns the absolute value of a BigInt.
BigInt abs(const BigInt& num) {
    return num < 0 ? -num : num;
}

// /*  Returns base^exp. Uses the fast Square and Multiply algorithm. 
//     https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Recursive_version
// */
// BigInt pow(const BigInt& base, BigInt exp) {
//     // Checking for edge cases
//     if (exp < 0) {
//         if (base == 0)
//             throw std::logic_error("Cannot divide by zero");
//         return abs(base) == 1 ? base : 0;
//     }
//     if (exp == 0) {
//         if (base == 0)
//             throw std::logic_error("Zero cannot be raised to zero");
//         return 1;
//     }

//     BigInt result("1");
//     while (exp){
//         if (exp % 2 == 1){
            
//         }
//     }
//     BigInt result = base, result_odd = 1;
//     while (exp > 1) {
//         if (exp % 2 ==)
//             result_odd *= result;
//         result *= result;
//         exp /= 2;
//     }

//     return result * result_odd;
// }

// // Returns the greatest common divisor (GCD, a.k.a. HCF) of two BigInts using Euclid's algorithm.
// BigInt gcd(const BigInt &num1, const BigInt &num2){
//     BigInt abs_num1 = abs(num1);
//     BigInt abs_num2 = abs(num2);

//     // base cases:
//     if (abs_num2 == 0)
//         return abs_num1;    // gcd(a, 0) = |a|
//     if (abs_num1 == 0)
//         return abs_num2;    // gcd(0, a) = |a|

//     BigInt remainder = abs_num2;
//     while (remainder != 0) {
//         remainder = abs_num1 % abs_num2;
//         abs_num1 = abs_num2;    // previous remainder
//         abs_num2 = remainder;   // current remainder
//     }

//     return abs_num1;
// }

// // Returns the least common multiple (LCM) of two BigInts.
// BigInt lcm(const BigInt& num1, const BigInt& num2) {
//     if (num1 == 0 or num2 == 0)
//         return 0;

//     return abs(num1 * num2) / gcd(num1, num2);
// }

#endif  
