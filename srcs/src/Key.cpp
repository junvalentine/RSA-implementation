#include "Key.h"
#include "PrimeGen.cpp"

// for the requirement of assignment
void calcPrivateExponent(mpz_class publicExponent, mpz_class prime1, mpz_class prime2, mpz_class &privateExponent, mpz_class &exponent1, mpz_class &exponent2, mpz_class &coefficient){
    mpz_class phi = (prime1 - 1) * (prime2 - 1);
    privateExponent = inverseMod(publicExponent, phi);
    exponent1 = privateExponent % (prime1 - 1);
    exponent2 = privateExponent % (prime2 - 1);
    coefficient = inverseMod(prime2, prime1);
}

void PrivateKey::genPrivKey(long long bits, bool defaultE){
    // generate public exponent 
    if (defaultE){
        publicExponent = 65537;
    }
    else{
        publicExponent = getPrime(bits);
    }
    // generate prime number
    mpz_class p= getPrime(bits);
    while(gcd(p, publicExponent) != 1){
        p = getPrime(bits);
    }
    prime1 = p;
    mpz_class q = getPrime(bits);
    while(gcd(q, publicExponent) != 1){
        q = getPrime(bits);
    }
    prime2 = q;
    // calculate modulus
    modulus = prime1 * prime2;
    
    // calculate private exponent
    calcPrivateExponent(publicExponent, prime1, prime2, privateExponent, exponent1, exponent2, coefficient);
    
}

void PublicKey::getPubKey(const PrivateKey &prk){
    modulus = prk.modulus;
    publicExponent = prk.publicExponent;
}