#include <iostream>
#include <chrono>
#include <fstream>
#include "Rsa.cpp"
int main(){
    std::srand(time(nullptr));
    std::string option;
    RSA rsa = RSA();

    while (true){
        std::cout << "1.GenKey" << std::endl;
        std::cout << "2.Encrypt" << std::endl;
        std::cout << "3.Decrypt / DecryptCRT" << std::endl;
        std::cout << "4.Encrypt File" << std::endl;
        std::cout << "5.Decrypt File" << std::endl;
        std::cout << "6.Encrypt OAEP" << std::endl;
        std::cout << "7.Decrypt OAEP" << std::endl;
        std::cout << "8.Exit" << std::endl;

        std::cout << "Options? "; 
        std::cin >> option;

        if (option == "1"){
            long long bits;
            std::cout << "Bits: ";
            std::cin >> bits;
            rsa.len = bits;
            auto start = std::chrono::high_resolution_clock::now();
            rsa.genKey(bits);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Key generated!" << std::endl;
            std::cout << "Time taken to gen keys: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "2"){
            std::string message;
            std::cout<< "Message: ";
            std::getline(std::cin >> std::ws, message);

            auto start = std::chrono::high_resolution_clock::now();
            std::string encrypted = rsa.encrypt(message);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Encrypted hex: " << bytes_to_hex(encrypted) << std::endl;
            std::cout << "Time taken to encrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "3"){
            std::string mode;
            std::cout << "Mode ? (Normal, CRT) ";
            std::cin >> mode;

            std::string ciphertext;
            std::cout<<"Ciphertext hex: ";
            std::getline(std::cin >> std::ws, ciphertext);

            std::string decrypted;
            auto start = std::chrono::high_resolution_clock::now();
            if (mode == "Normal"){
                decrypted = rsa.decrypt(hex_to_bytes(ciphertext));
            }
            else if (mode == "CRT"){
                decrypted = rsa.decryptCRT(hex_to_bytes(ciphertext));
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Decrypted hex: " << decrypted << std::endl;
            std::cout << "Decrypted message: " << decrypted << std::endl;
            std::cout << "Time taken to decrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "4") {
            std::string inputFile, outputFile;
            std::cout << "Input file: ";
            std::cin >> inputFile;
            std::cout << "Output file (encrypted): ";
            std::cin >> outputFile;

            // Read the input file
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                continue;
            }
            std::string plaintext((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            // Encrypt the file content
            auto start = std::chrono::high_resolution_clock::now();
            std::string encrypted = rsa.encrypt(plaintext);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            // Write the encrypted content to the output file
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                std::cerr << "Error opening output file." << std::endl;
                continue;
            }
            outFile << encrypted; // Write as hex
            outFile.close();

            std::cout << "File encrypted successfully!" << std::endl;
            std::cout << "Time taken to encrypt: " << elapsed.count() << " seconds" << std::endl;
        } else if(option == "5") {
            std::string inputFile, outputFile, mode;
            std::cout << "Input file (encrypted): ";
            std::cin >> inputFile;
            std::cout << "Output file (decrypted): ";
            std::cin >> outputFile;
            std::cout << "Mode ? (Normal, CRT): ";
            std::cin >> mode;

            // Read the encrypted file
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                continue;
            }
            std::string encrypted((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            // Decrypt the file content
            auto start = std::chrono::high_resolution_clock::now();
            std::string decrypted;
            if (mode == "Normal") {
                decrypted = rsa.decrypt(encrypted);
            } else if (mode == "CRT") {
                decrypted = rsa.decryptCRT(encrypted);
            } else {
                std::cerr << "Invalid mode. Use 'Normal' or 'CRT'." << std::endl;
                continue;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            // Write the decrypted content to the output file
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                std::cerr << "Error opening output file." << std::endl;
                continue;
            }
            outFile << decrypted; // Write plaintext
            outFile.close();

            std::cout << "File decrypted successfully!" << std::endl;
            std::cout << "Time taken to decrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "6"){
            std::string inputFile, outputFile;
            std::cout << "Input file: ";
            std::cin >> inputFile;
            std::cout << "Output file (encrypted): ";
            std::cin >> outputFile;

            // Read the input file
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                continue;
            }
            std::string plaintext((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            // Encrypt the file content
            auto start = std::chrono::high_resolution_clock::now();
            std::string encrypted = rsa.OAEP_encrypt(plaintext);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            // Write the encrypted content to the output file
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                std::cerr << "Error opening output file." << std::endl;
                continue;
            }
            outFile << encrypted; // Write as hex
            outFile.close();

            std::cout << "File encrypted successfully!" << std::endl;
            std::cout << "Time taken to encrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "7"){
            std::string inputFile, outputFile, mode;
            std::cout << "Input file (encrypted): ";
            std::cin >> inputFile;
            std::cout << "Output file (decrypted): ";
            std::cin >> outputFile;

            // Read the encrypted file
            std::ifstream inFile(inputFile, std::ios::binary);
            if (!inFile.is_open()) {
                std::cerr << "Error opening input file." << std::endl;
                continue;
            }
            std::string encrypted((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();

            // Decrypt the file content
            auto start = std::chrono::high_resolution_clock::now();
            std::string decrypted;
            decrypted = rsa.OAEP_decrypt(encrypted);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            // Write the decrypted content to the output file
            std::ofstream outFile(outputFile, std::ios::binary);
            if (!outFile.is_open()) {
                std::cerr << "Error opening output file." << std::endl;
                continue;
            }
            outFile << decrypted; // Write plaintext
            outFile.close();

            std::cout << "File decrypted successfully!" << std::endl;
            std::cout << "Time taken to decrypt: " << elapsed.count() << " seconds" << std::endl;
        }
        else if(option == "8"){
            break;
        }
        else{
            std::cout << "Invalid option!" << std::endl;
        }
    }
}