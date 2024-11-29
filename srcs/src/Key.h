#ifndef KEY_H
#define KEY_H

#include "gmpxx.h"

class PrivateKey{
    public:
        mpz_class modulus; // n
        mpz_class publicExponent; // e
        mpz_class privateExponent; // d
        mpz_class prime1; // p
        mpz_class prime2; // q
        // three next field is optional, this is for RSA-CRT
        mpz_class exponent1; // dp
        mpz_class exponent2; // dq
        mpz_class coefficient; // qInv
        void genPrivKey(long long bits, bool defaultE);
};

class PublicKey{
    public:
        mpz_class modulus; // n
        mpz_class publicExponent; // e
        void getPubKey(const PrivateKey &prk);
};

#endif 