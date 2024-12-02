#include <iostream>
#include <cassert>

#include "../src/Sha2.cpp"
#include "../src/Math.cpp"
int main(){
    std::string msg="";
    std::cout<<sha256(msg);
}