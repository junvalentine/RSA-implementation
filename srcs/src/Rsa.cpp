#include "Rsa.h"
RSA:: RSA(){
}

RSA::RSA(long long bits){
    privateKey.genPrivKey(bits, true);
    publicKey.getPubKey(privateKey);
}

RSA::RSA(PrivateKey privateKey){
    this->privateKey = privateKey;
    publicKey.getPubKey(privateKey);
}

RSA::RSA(PublicKey publicKey){
    this->publicKey = publicKey;
}

void RSA::importPrivKey(PrivateKey privateKey){
    this->privateKey = privateKey;
    publicKey.getPubKey(privateKey);
}

void RSA::importPublicKey(PublicKey publicKey){
    this->publicKey = publicKey;
}

void RSA::genKey(long long bits){
    privateKey.genPrivKey(bits, true);
    publicKey.getPubKey(privateKey);
}

std::string RSA::encrypt(std::string message){
    mpz_class message_mpz = bytes_to_mpz(message);
    mpz_class encrypted = encrypt(message_mpz);
    return bytes_to_hex(mpz_to_bytes(encrypted));
}

std::string RSA::decrypt(std::string message){
    mpz_class message_mpz = bytes_to_mpz(message);
    mpz_class decrypted = decrypt(message_mpz);
    return bytes_to_hex(mpz_to_bytes(decrypted));
}

std::string RSA::decryptCRT(std::string message){
    mpz_class message_mpz = bytes_to_mpz(message);
    mpz_class decrypted = decryptCRT(message_mpz);
    return bytes_to_hex(mpz_to_bytes(decrypted));
}

mpz_class RSA::encrypt(mpz_class message){
    return powerMod(message, publicKey.publicExponent, publicKey.modulus);
}

mpz_class RSA::decrypt(mpz_class message){
    return powerMod(message, privateKey.privateExponent, privateKey.modulus);
}

mpz_class RSA::decryptCRT(mpz_class message){
    mpz_class m1 = powerMod(message, privateKey.exponent1, privateKey.prime1);
    mpz_class m2 = powerMod(message, privateKey.exponent2, privateKey.prime2);
    mpz_class h = privateKey.coefficient * (m1 - m2) % privateKey.prime1;
    return m2 + h * privateKey.prime2;
}