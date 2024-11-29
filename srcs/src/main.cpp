#include <iostream>
#include "Rsa.cpp"

int main(){
    std::srand(time(nullptr));
    std::string option;
    RSA rsa = RSA();

    while (true){
        std::cout << "Options?"<<std::endl; 
        std::cin >> option;

        if (option == "1"){
            std::string p;
            std::string q;
            std::cin >> p;
            std::cin >> q;
            mpz_class prime1(p);
            mpz_class prime2(q);
            
        }
    }
}