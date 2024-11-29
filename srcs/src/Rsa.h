/*
    RSA class
*/

#ifndef RSA_H_
#define RSA_H_

#include "Key.cpp"

class RSA
{   
    private:
        PrivateKey privateKey;
        PublicKey publicKey;
	public:
        RSA();
        // generate key pair with given bits
        RSA(long long bits);
        // import privatekey, calculate publickey
        RSA(PrivateKey privateKey);
        // import publickey, can only be use for encrypt message
        RSA(PublicKey publicKey);

        void genKey(long long bits);
        void importPrivKey(PrivateKey privateKey);
        void importPublicKey(PublicKey publicKey);
        
        std::string encrypt(std::string message);
        std::string decrypt(std::string message);
        std::string decryptCRT(std::string message);

        mpz_class encrypt(mpz_class message);
        mpz_class decrypt(mpz_class message);
        mpz_class decryptCRT(mpz_class message);
};

#endif 
