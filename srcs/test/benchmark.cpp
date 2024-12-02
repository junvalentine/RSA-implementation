#include <iostream>
#include <chrono>
#include <string>
#include "../src/Rsa.cpp" // Include your RSA implementation header
int main() {
    std::srand(time(nullptr));
    mpz_class number = getRandomNumber(1024);
    std::string message = mpz_to_bytes(number);
    RSA rsa = RSA();
    rsa.genKey(1024);
    std::string encrypted = rsa.encrypt(message);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 50; ++i) {
        rsa.genKey(1024);
        // mpz_class number = getRandomNumber(1024);
        // mpz_class dec = rsa.encrypt(number);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double average_time = duration.count() / 100;

    std::cout << "Average encryption time: " << average_time << " seconds" << std::endl;

    return 0;
}