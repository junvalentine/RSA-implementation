#include "../src/PrimeGen.cpp"
#include <iostream>
#include <cassert>

void test_is_prime() {
    mpz_class prime1("2");
    mpz_class prime2("3");
    mpz_class prime3("5");
    mpz_class prime4("7");
    mpz_class non_prime1("4");
    mpz_class non_prime2("6");
    mpz_class non_prime3("8");
    mpz_class non_prime4("9");

    assert(isPrime(prime1) == true);
    assert(isPrime(prime2) == true);
    assert(isPrime(prime3) == true);
    assert(isPrime(prime4) == true);
    assert(isPrime(non_prime1) == false);
    assert(isPrime(non_prime2) == false);
    assert(isPrime(non_prime3) == false);
    assert(isPrime(non_prime4) == false);

    std::cout << "Prime test passed!" << std::endl;
}

void test_generate_prime() {
    mpz_class prime = getPrime(1024); // Assuming generatePrime generates a prime number of 128 bits
    assert(isPrime(prime) == true);
    std::cout << "Generated prime: " << prime << std::endl;
    std::cout << "Generate prime test passed!" << std::endl;
}
void test_generate_random(){
    std::cout<<getRandomNumber(1024)<<std::endl;
    std::cout<<getRandomRange(100, 200)<<std::endl;
    std::cout<<getPrimeCandidate(1024)<<std::endl;
    std::cout << "Generate random test passed!" << std::endl;
}

int main() {
    std::srand(time(nullptr));
    test_generate_random();
    test_is_prime();
    test_generate_prime();
    return 0;
}