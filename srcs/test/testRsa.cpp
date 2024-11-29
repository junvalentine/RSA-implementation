#include "../src/Rsa.cpp"
#include <iostream>
#include <cassert>

void test_RSA() {
    RSA rsa = RSA();
    rsa.genKey(1024);
    std::string message = "Hello, World!";
    std::string encrypted = rsa.encrypt(message);
    std::cout << "Encrypted hex: " << encrypted << std::endl;
    std::string decrypted = rsa.decrypt(hex_to_bytes(encrypted));
    std::cout << "Decrypted hex: " << decrypted << std::endl;
    std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
    assert(message == hex_to_bytes(decrypted));
    std::cout << "RSA test passed!" << std::endl;
}

void test_RSA1() {
    RSA rsa = RSA(1024);
    std::string message = "Hello, World!";
    std::string encrypted = rsa.encrypt(message);
    std::cout << "Encrypted hex: " << encrypted << std::endl;
    std::string decrypted = rsa.decrypt(hex_to_bytes(encrypted));
    std::cout << "Decrypted hex: " << decrypted << std::endl;
    std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
    assert(message == hex_to_bytes(decrypted));
    std::cout << "RSA1 test passed!" << std::endl;
}

void test_RSA2(){
    PrivateKey privateKey;
    privateKey.genPrivKey(1024, true);
    RSA rsa = RSA(privateKey);
    std::string message = "Hello, World!";
    std::string encrypted = rsa.encrypt(message);
    std::cout << "Encrypted hex: " << encrypted << std::endl;
    std::string decrypted = rsa.decrypt(hex_to_bytes(encrypted));
    std::cout << "Decrypted hex: " << decrypted << std::endl;
    std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
    assert(message == hex_to_bytes(decrypted));
    std::cout << "RSA2 test passed!" << std::endl;
}

void test_RSA3(){
    PrivateKey privateKey;
    privateKey.genPrivKey(1024, true);
    RSA rsa1 = RSA(privateKey);
    PublicKey publicKey;
    publicKey.getPubKey(privateKey);
    RSA rsa2 = RSA(publicKey);

    std::string message = "Hello, World!";
    std::string encrypted = rsa2.encrypt(message);
    std::cout << "Encrypted hex: " << encrypted << std::endl;
    std::string decrypted = rsa1.decrypt(hex_to_bytes(encrypted));
    std::cout << "Decrypted hex: " << decrypted << std::endl;
    std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
    assert(message == hex_to_bytes(decrypted));
    std::cout << "RSA3 test passed!" << std::endl;
}

int main(){
    test_RSA();
    test_RSA1();
    test_RSA2();
    test_RSA3();
    return 0;
}
