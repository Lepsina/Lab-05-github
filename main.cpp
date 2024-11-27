#include <iostream>
#include <string>
#include <typeinfo>
#include "class.h"
void f(BigInt n){}
int main(){

    BigInt a;
    BigInt b;
    
    std::cin >> a >> b;
    int ai = int(a), bi = int(b);
    std::cout << "\n";
    std::cout << a / b << " " << a % b << "\n";
    std::cout << a / -b << " " << a % -b << "\n";
    std::cout << -a / -b << " " << -a % -b << "\n";
    std::cout << -a / b << " " << -a % b << "\n";
    std::cout << "------------------\n";
    std::cout << ai / bi << " " << ai % bi << "\n";
    std::cout << ai / -bi << " " << ai % -bi << "\n";
    std::cout << -ai / -bi << " " << -ai % -bi << "\n";
    std::cout << -ai / bi << " " << -ai % bi << "\n";

    return 0;
}
