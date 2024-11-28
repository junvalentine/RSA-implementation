// Reimplementation of complex function in BigInt
#include "BigInt.cpp"
#include <iostream>
/*  Normal exponential function using the fast Square and Multiply algorithm.
    https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Recursive_version
*/
BigInt power(BigInt base, BigInt exp) {
    // Check edge cases
    if (exp < 0) {
        throw "Not support negative exponent";
    }
    else if (exp == 0) {
        if (base == 0){
            throw "Zero cannot be raised to zero";
        }   
        return 1;
    }

    BigInt result = 1;
    while (exp > 0) {
        if (exp % 2 == 1){
            result *= base;
        }
        exp /= 2;
        base = base * base;
    }

    return result;
}

/*  Modular exponential function using the fast Square and Multiply algorithm.
    https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
*/
BigInt powerMod(BigInt base, BigInt exp, BigInt modulo){
    // Check edge cases
    if (exp < 0) {
        throw "Not support negative exponent";
    }
    else if (exp == 0) {
        if (base == 0){
            throw "Zero cannot be raised to zero";
        }   
        return 1;
    }

    BigInt result = 1;
    base = base % modulo;

    while (exp > 0) {
        if (exp % 2 == 1){
            result *= base;
            result %= modulo;
        }
        exp /= 2;
        base = (base * base) % modulo;
    }

    return result;
}

/*  Greatest Common Divisor function using Euclidean algorithm.
    https://en.wikipedia.org/wiki/Greatest_common_divisor#Euclidean_algorithm
    https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
*/
BigInt gcd(const BigInt &a, const BigInt &b){
    if (b == 0){
        return a;
    }
    else{
        return gcd(b, a % b);
    }
}

/*  Modular multiplicative inverse
    https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode
*/
BigInt inverseMod(BigInt base, BigInt modulo){
    // check gcd equal to 1
    if (gcd(base, modulo) > 1) {
        throw "gcd is not one";
    }

    BigInt s = 0, old_s = 1;
    BigInt r = modulo, old_r = base;
    BigInt quotient;

    while(r > 0){
        quotient = old_r / r;
        std::tie(old_r, r) = std::make_tuple(r, old_r - quotient * r);
        std::tie(old_s, s) = std::make_tuple(s, old_s - quotient * s);
    }
    
    return old_s;
}