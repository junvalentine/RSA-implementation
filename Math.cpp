// Math helper functions
#include <gmpxx.h> 

/*  Normal exponential function using the fast Square and Multiply algorithm.
    https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Recursive_version
*/
mpz_class power(mpz_class base, mpz_class exp) {
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

    mpz_class result = 1;
    while (exp > 0) {
        if (exp % 2 == 1){
            result *= base;
        }
        exp /= 2;
        base = base * base;
    }

    return result;
}

// /*  Modular exponential function using the fast Square and Multiply algorithm.
//     https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
// */
mpz_class powerMod(mpz_class base, mpz_class exp, mpz_class modulo){
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

    mpz_class result = 1;
    base = base % modulo;

    while (exp > 0) {
        if (exp % 2 == 1){
            result = (result * base) % modulo;
        }
        exp = exp / 2;
        base = (base * base) % modulo;
    }

    return result;
}

// /*  Greatest Common Divisor function using Euclidean algorithm.
//     https://en.wikipedia.org/wiki/Greatest_common_divisor#Euclidean_algorithm
//     https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
// */
mpz_class gcd(const mpz_class &a, const mpz_class &b){
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
mpz_class inverseMod(mpz_class base, mpz_class modulo){
    // check gcd equal to 1
    if (gcd(base, modulo) > 1) {
        throw "gcd is not one";
    }

    mpz_class s = 0, old_s = 1;
    mpz_class r = modulo, old_r = base;
    mpz_class quotient;

    while(r > 0){
        quotient = old_r / r;
        mpz_class temp_old_r = old_r; 
        old_r = r;                    
        r = temp_old_r - quotient * r;

        mpz_class temp_old_s = old_s; 
        old_s = s;                   
        s = temp_old_s - quotient * s; 
    }
    if (old_s < 0){
        old_s += modulo;
    }
    return old_s;
}

long long bit_length(mpz_class num){
    long long res = 0;
    while (num > 0){
        res+=1;
        num = num / 2;
    }
    return res;
}