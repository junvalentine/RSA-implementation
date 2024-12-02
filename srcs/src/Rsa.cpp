#include "Rsa.h"
#include "Sha2.cpp"

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
    return mpz_to_bytes(encrypted);
}

std::string RSA::decrypt(std::string message){
    mpz_class message_mpz = bytes_to_mpz(message);
    mpz_class decrypted = decrypt(message_mpz);
    return mpz_to_bytes(decrypted);
}

std::string RSA::decryptCRT(std::string message){
    mpz_class message_mpz = bytes_to_mpz(message);
    mpz_class decrypted = decryptCRT(message_mpz);
    return mpz_to_bytes(decrypted);
}

mpz_class RSA::encrypt(mpz_class message){
    if (message >= publicKey.modulus){
        throw std::invalid_argument("Message is too large");
    }
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

std::string MGF(std::string seed, long long maskLen){
    std::string T;
    long long hLen = 32;
    long long l = (maskLen + hLen - 1) / hLen;
    for (long long i = 0; i < l; i++){
        
        std::string C = seed + mpz_to_bytes(mpz_class(std::to_string(i)), true, 4);
        T += sha256(seed + C);
    }
    return T.substr(0, maskLen);
}

std::string RSA::OAEP_encrypt(std::string message, std::string label = ""){
    long long k = this->len / 4;
    long long mLen = message.size();
    long long hLen = 32;
    long long PSlen = k - mLen - 2 * hLen - 2;
    if (PSlen < 0){
        throw std::invalid_argument("Message too long");
    }
    
    std::string PS(PSlen, 0);
    std::string DB = hex_to_bytes(sha256(label)) + PS + '\x01' + message;
    std::string seed = mpz_to_bytes(getRandomNumber(hLen*8), 32);
    
    std::string dbMask = MGF(seed, k - hLen - 1);
    std::string maskedDB = xor_string(DB, dbMask);
    std::string seedMask = MGF(maskedDB, hLen);
    std::string maskedSeed = xor_string(seed, seedMask);
    std::string em = '\x00' + maskedSeed + maskedDB;    
    return encrypt(em);
}

std::string RSA::OAEP_decrypt(std::string ciphertext, std::string label=""){
    long long k = this->len / 4;
    std::string em = mpz_to_bytes(decrypt(bytes_to_mpz(ciphertext)),true, k);
    // if (em.size() != k){
    //     throw std::invalid_argument("Decryption error");
    // }

    long long hLen = 32;
    std::string maskedSeed = em.substr(1, hLen);
    std::string maskedDB = em.substr(hLen + 1);
    std::string seedMask = MGF(maskedDB, hLen);
    std::string seed = xor_string(maskedSeed, seedMask);
    std::string dbMask = MGF(seed, k - hLen - 1);
    std::string DB = xor_string(maskedDB, dbMask);
    if (DB.substr(0, hLen) != hex_to_bytes(sha256(label))){
        throw std::invalid_argument("Decryption error");
    }
    long long i = hLen;
    while (DB[i] == '\x00'){
        i++;
    }
    if (DB[i] != '\x01'){
        throw std::invalid_argument("Decryption error");
    }
    i++;
    return DB.substr(i);
}