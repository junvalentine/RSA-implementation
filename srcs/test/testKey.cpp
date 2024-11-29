#include "../src/Key.cpp"
#include <iostream>
#include <cassert>

int main(){

    PrivateKey privateKey;
    privateKey.genPrivKey(1024, true);
    std::cout << "Modulus: " << privateKey.modulus << std::endl;
    std::cout << "Public Exponent: " << privateKey.publicExponent << std::endl;
    std::cout << "Private Exponent: " << privateKey.privateExponent << std::endl;
    std::cout << "Prime 1: " << privateKey.prime1 << std::endl;
    std::cout << "Prime 2: " << privateKey.prime2 << std::endl;

    assert(privateKey.modulus == privateKey.prime1 * privateKey.prime2);
    assert(privateKey.privateExponent == inverseMod(privateKey.publicExponent, (privateKey.prime1 - 1) * (privateKey.prime2 - 1)));
    assert(privateKey.exponent1 == privateKey.privateExponent % (privateKey.prime1 - 1));
    assert(privateKey.exponent2 == privateKey.privateExponent % (privateKey.prime2 - 1));
    assert(privateKey.coefficient == inverseMod(privateKey.prime2, privateKey.prime1));


    PublicKey publicKey;
    publicKey.getPubKey(privateKey);
    std::cout << "Modulus: " << publicKey.modulus << std::endl;
    std::cout << "Public Exponent: " << publicKey.publicExponent << std::endl;

    return 0;
}