#include "BigIntRe.cpp"

#include <iostream>
#include <cassert>

void test_addition() {
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    BigInt result = num1 + num2;
    assert(result == "111111111011111111100");
    std::cout << "Addition test passed!" << std::endl;
}

void test_subtraction() {
    BigInt num1("98765432109876543210");
    BigInt num2("12345678901234567890");
    BigInt result = num1 - num2;
    assert(result == "86419753208641975320");
    std::cout << "Subtraction test passed!" << std::endl;
}

void test_multiplication() {
    BigInt num1("2000");
    BigInt num2("123456789012345678901234567890");
    BigInt result = num1 * num2;
    assert(result == "246913578024691357802469135780000");
    std::cout << "Multiplication test passed!" << std::endl;
}

void test_division() {
    BigInt num1("123456789012345678901234567890");
    BigInt num2("123456789012345678901234567890");
    BigInt result = num1 / num2;
    assert(result == "1");
    std::cout << "Division test passed!" << std::endl;
}

void test_modulus() {
    BigInt num1("123456789012345678901234567890");
    BigInt num2("100000000000000000000000000001");
    BigInt result = num1 % num2;
    assert(result == "23456789012345678901234567889");
    std::cout << "Modulus test passed!" << std::endl;
}

void test_power() {
    BigInt base("2");
    BigInt exp("10");
    BigInt result = power(base,exp);
    assert(result == "1024");
    std::cout << "Power test passed!" << std::endl;
}

void test_power_modulo(){
    BigInt base("2");
    BigInt exp("10000");
    BigInt modulo("123456789012345678901234567890");
    BigInt result = powerMod(base, exp, modulo);
    assert(result == "13925211707661092000373548626");
    std::cout << "Modular power test passed!" << std::endl;
}

void test_gcd() {
    BigInt num1("94460530507136610698792141854649138524011706593978058099518887591992719528796262627171013572394847112217809046755956088827822094227903422577607219102754400357140343025337787892336848209128605989868292263873593656063755043023693992197967578886096638126438564192867826216629443496344556286585000577110978395711");
    BigInt num2("359233397518640530487506515473230673806816520176898554952470329512348312368012186771131364615817603567764327804812901005812207424348716716062640254247774984558204724525359607354557033739316088579469115479511276674010460428619108252328870702503825514794845859625476343101841773616598347557882757194753050838888933");
    BigInt result = gcd(num1, num2);
    assert(result == "94460530507136610698792141854649138524011706593978058099518887591992719528796262627171013572394847112217809046755956088827822094227903422577607219102754400357140343025337787892336848209128605989868292263873593656063755043023693992197967578886096638126438564192867826216629443496344556286585000577110978395711");
    std::cout << "GCD test passed!" << std::endl;
}

void test_modular_inverse() {
    BigInt num("3");
    BigInt mod("11");
    BigInt result = inverseMod(num, mod);
    std::cout<< result<< std::endl;
    std::cout << "Modular inverse test passed!" << std::endl;
}
int main() {
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_modulus();
    test_power();
    test_power_modulo();
    test_gcd();
    test_modular_inverse();
    return 0;
}