/*
    Prime generator for RSA implementation
*/
#include "Math.cpp"

/*
    Generates random number with n bits using rand().
*/
mpz_class getRandomNumber(long long n){
    mpz_class number = std::rand() % 2;
    for (long long i = 1; i < n; i++){
        number *= 2;
        number += std::rand() % 2;
    }
    return number;
}

/*
    Generates prime candidates. This is getRandomNumber() but the last bit is 1.
    This will speed up the prime generation process.
*/
mpz_class getPrimeCandidate(long long n){
    return getRandomNumber(n-1) * 2 + 1;
}

/*
    Generates a random number in a specified range [min,max].
*/
mpz_class getRandomRange(const mpz_class &min, const mpz_class &max){
    mpz_class range = max - min;
    long long bits = (std::rand() % bit_length(range)) + 1;
    mpz_class value = getRandomNumber(bits);
    while (value > range){
        value = getRandomNumber(bits);
    }
    return value + min;
}
/*
    Miller Rabin testing 
    https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Miller%E2%80%93Rabin_test
    k is number of iterations. Probability of error is 4^-k.
*/
bool isPrime(const mpz_class &number, unsigned long int k = 100){
    // Check edge cases
    if (number < 2){
        return false;
    }
    else if (number < 4){
        return true;
    }
    else if (number % 2 == 0){
        return false;
    }

    // Write number as 2^s * d + 1
    mpz_class numberMinusOne = number - 1;
    mpz_class s = 0;
    mpz_class d = numberMinusOne;
    while (d % 2 == 0){
        d /= 2;
        s++;
    }

    // Test with k different possible witnesses
    mpz_class temp, x, a;
    for (unsigned long int i = 0; i < k; i++){
        a = getRandomRange(2, number - 1);
        x = powerMod(a, d, number);

        for (long int r = 0; r < s; r++){
            temp = powerMod(x, 2, number);
            if (x != 1 && temp == 1 && x != number - 1){
                return false; // A composite number
            }
            x = temp;
        }
        if (temp != 1){
            return false; // A composite number
        }
    }
    return true; // A probable prime
}

// Generate prime number with n bits
mpz_class getPrime(long long n){
    mpz_class candidate = getPrimeCandidate(n);
    
    while (!isPrime(candidate, 10)){
        candidate += 2;
        if (bit_length(candidate) > n){
            candidate = getPrimeCandidate(n);
        }
    }
    return candidate;
}