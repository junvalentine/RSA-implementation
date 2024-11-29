#include <iostream>
#include <chrono>

#include "Rsa.cpp"
int main(){
    std::srand(time(nullptr));
    std::string option;
    RSA rsa = RSA();

    while (true){
        std::cout << "1.GenKey" << std::endl;
        std::cout << "2.Encrypt" << std::endl;
        std::cout << "3.Decrypt" << std::endl;
        std::cout << "4.DecryptCRT" << std::endl;
        std::cout << "5.Exit" << std::endl;

        std::cout << "Options? "; 
        std::cin >> option;

        if (option == "1"){
            long long bits;
            std::cout << "Bits: ";
            std::cin >> bits;
            auto start = std::chrono::high_resolution_clock::now();
            rsa.genKey(bits);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Key generated!" << std::endl;
            std::cout << "Time taken to gen keys: " << elapsed.count() << " seconds" << std::endl;
        }
        // else if(option == "")
        else if(option == "2"){
            std::string message;
            std::cout<<"Message: ";
            std::cin >> message;

            auto start = std::chrono::high_resolution_clock::now();
            std::string encrypted = rsa.encrypt(message);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Encrypted hex: " << encrypted << std::endl;
            std::cout << "Time taken to encrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "3"){
            std::string ciphertext;
            std::cout<<"Ciphertext hex: ";
            std::cin >> ciphertext;

            auto start = std::chrono::high_resolution_clock::now();
            std::string decrypted = rsa.decrypt(hex_to_bytes(ciphertext));
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Decrypted hex: " << decrypted << std::endl;
            std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
            std::cout << "Time taken to decrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "4"){
            std::string ciphertext;
            std::cout<<"Ciphertext hex: ";
            std::cin >> ciphertext;

            auto start = std::chrono::high_resolution_clock::now();
            std::string decrypted = rsa.decryptCRT(hex_to_bytes(ciphertext));
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Decrypted hex: " << decrypted << std::endl;
            std::cout << "Decrypted message: " << hex_to_bytes(decrypted) << std::endl;
            std::cout << "Time taken to decrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "5"){
            break;
        }
    }
}