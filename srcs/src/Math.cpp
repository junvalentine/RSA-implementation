// Math helper functions
#include <gmpxx.h> 
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

/*  Modular exponential function using the fast Square and Multiply algorithm.
    https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
    https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Recursive_version
*/
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

/*  Greatest Common Divisor function using Euclidean algorithm.
    https://en.wikipedia.org/wiki/Greatest_common_divisor#Euclidean_algorithm
     https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
*/
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

mpz_class bytes_to_mpz(const std::string& bytes, bool big_endian = true) {
    mpz_class number;
    mpz_import(number.get_mpz_t(), bytes.size(), 
               big_endian ? 1 : -1, // Word order (1 = big-endian, -1 = little-endian)
               1, 0, 0, bytes.data());
    return number;
}

std::string mpz_to_bytes(const mpz_class& number, bool big_endian = true) {
    size_t size = (mpz_sizeinbase(number.get_mpz_t(), 2) + 7) / 8; // Determine byte size
    std::string bytes(size, 0);
    mpz_export(&bytes[0], nullptr, 
               big_endian ? 1 : -1, // Word order (1 = big-endian, -1 = little-endian)
               1, 0, 0, number.get_mpz_t());
    return bytes;
}

std::string bytes_to_hex(const std::string& bytes) {
    std::ostringstream hex_stream;
    for (unsigned char byte : bytes) {
        hex_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return hex_stream.str();
}

std::string hex_to_bytes(const std::string& hex) {
    // Ensure the input string has an even number of characters
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even number of characters.");
    }

    std::string bytes;
    bytes.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2) {
        // Take two characters from the hex string
        std::string byteString = hex.substr(i, 2);

        // Convert the hex string to a byte
        unsigned char byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}