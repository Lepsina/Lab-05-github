
#include "class.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

//constructors
BigInt::BigInt() {value = "0"; sign = true;}           //defolt constructor
BigInt::BigInt(bool insign, std::string str) {     //bool + string
    sign = insign;
    value = str;
    while (value.size() > 1 && value[0] == '0') {
            value.erase(0, 1);
    }
    if (value == "0") sign = true;
}
BigInt::BigInt(std::string& str) {                  //string constructor
    sign = str[0] == '-' ? false : true;
    value = sign ? str : str.substr(1);
}
BigInt::BigInt(const char* str) {                   //cstring constructor
    sign = str[0] == '-' ? false : true;
    value = sign ? std::string(str) : std::string(str + 1);
} 
BigInt::BigInt(int num){                            //int constructor
    std::stringstream ss;
    ss << num;              
    std::string str = ss.str();
    sign = str[0] == '-' ? false : true;
    value = sign ? str : str.substr(1);
    
}
BigInt::BigInt(short num){                          //short constructor
     std::stringstream ss;
    ss << num;              
    std::string str = ss.str();
    sign = str[0] == '-' ? false : true;
    value = sign ? str : str.substr(1);
}
BigInt::BigInt(long num){                           //long  constructor
    std::stringstream ss;
    ss << num;              
    std::string str = ss.str();
    sign = str[0] == '-' ? false : true;
    value = sign ? str : str.substr(1);
}
BigInt::BigInt(char num){                           //char  constructor
     std::stringstream ss;
    ss << num;              
    std::string str = ss.str();
    sign = str[0] == '-' ? false : true;
    value = sign ? str : str.substr(1);
}
BigInt::BigInt(BigInt const &obj){                  //copy constructor
    value = obj.value;
    sign = obj.sign;
    std::cout << "copy" << "\n";
}
BigInt::~BigInt(){}                                 //destructour

//dop functions
std::string stringDif(const std::string& big, const std::string& small){     //substract abs values
    std::string result;
    int b = big.size() - 1; int s = small.size() - 1;
    int dop = 0;
    while (b >= 0 || s >= 0){
        int dif, right = (s >= 0 ? small[s--] - '0' : 0), left = big[b--] - '0';
        dif = left - right - dop;
        if (dif < 0){
            dif += 10;
            dop = 1;
        } else {
            dop = 0;
        }
        result.push_back(dif + '0');
    }
    while(result.size() > 1 && result[result.size() - 1] == '0') {
            result.erase(result.size() - 1, 1);
    }

    std::reverse(result.begin(), result.end());
    return result.empty() ? "0" : result;
}   
std::string stringSum(const std::string& adin, const std::string& dva){     //sumarize abs values
    std::string result;
    int i = adin.size() - 1, j = dva.size() - 1;
    int dop = 0;
    while (i >= 0 || j >= 0 || dop == 1){
        int sum = 0;
        sum = (i >= 0 ? adin[i--] - '0' : 0) + (j >= 0 ? dva[j--] - '0' : 0) + dop;
        dop = sum / 10;
        result.push_back((sum % 10) + '0');
    }
    std::reverse(result.begin(), result.end());
    return result; 
}
std::string stringMultiply(const std::string& adin, const std::string& dva){    //multiply
    int a, d = dva.size() - 1;
    int dop = 0;
    std::string result = "0", tmp;
    while (d >= 0){
        tmp = "";
        a = adin.size() - 1;
        for (int i = 0; i < (int)dva.size() - d - 1; ++i){
            tmp.push_back('0');
        }
        while(a >= 0 || dop){
            int prod;
            prod = (a >= 0 ? adin[a--] - '0' : 1) * (dva[d] - '0') + dop;
            dop = prod / 10;
            tmp.push_back((prod % 10) + '0');
        }
        d--;
        std::reverse(tmp.begin(), tmp.end());
        result = stringSum(result, tmp);
    }
    return result;
}
bool firstBigger(const std::string& adin, const std::string& dva){     //compare abs values
    if(adin.length() > dva.length()) return true;
    if(adin.length() < dva.length()) return false;
    for (int i = 0; i < int(adin.length()); ++i){
        if (adin[i] > dva[i]) return true;
        if (adin[i] < dva[i]) return false;
    }
    return true;
}
void BigInt::removeZeros(){
    while (value[0] == '0')
        value.erase(value.begin());
}
std::string quotientDivision(const std::string& dividend, const std::string& divisor){ //return quotient
    size_t divsize = divisor.length();
    std::string dim = dividend.substr(0, divsize);
    std::string rem;
    std::string quotient = "";
    int p = divsize;
    std::string sub[10];
    sub[1] = divisor;
    if (divisor == dividend) return "1";
    if (firstBigger(dividend, divisor) == false) return "0";
    while(p != dividend.length() || divsize == dividend.length()){
   
        while(firstBigger(sub[1], dim)){
            if (p != dividend.length()){
                quotient += '0';
                dim += dividend[p++];
            } else {
                rem = dim;
                return quotient;
            }
        }
        for (int i = 2; i < 10; i++){
            if (sub[i] == "") sub[i] = stringSum(sub[i-1], divisor);
            if (firstBigger(sub[i], dim)){
                rem = stringDif(dim, (sub[i] == dim ? sub[i] : sub[--i]));
                rem = (rem == "0" ? "" : rem);
                quotient += (i + '0');
                break;
            }
        }

        dim = rem;
    }
    return quotient;
}
std::string remainderDivision(const std::string& dividend, const std::string& divisor){ //return remainder
    const size_t divsize = divisor.length();
    std::string dim = dividend.substr(0, divsize);
    std::string rem;
    std::string quotient = "";
    int p = divsize;
    std::string sub[10];
    sub[1] = divisor;
    if (divisor == dividend) return "0";
    if (firstBigger(dividend, divisor) == false) return dividend;
    while(p != dividend.length() || divsize == dividend.length()){
        std::cout << "      " << dim << ' ' << rem << '\n';
        while(firstBigger(sub[1], dim)){
            if (p != dividend.length()){
                quotient += '0';
                dim += dividend[p++];
            } else {
                rem = dim;
                return (rem == "" ? "0" : rem);
            }
        }
        for (int i = 2; i < 10; i++){
            if (sub[i] == "") sub[i] = stringSum(sub[i-1], divisor);
            if (firstBigger(sub[i], dim)){
                rem = stringDif(dim, (sub[i] == dim ? sub[i] : sub[--i]));
                rem = (rem == "0" ? "" : rem);
                quotient += (i + '0');
                break;
            }
        }

        dim = rem;
    }
    return (rem == "" ? "0" : rem) ;
}

//get set function
const std::string& BigInt::get_value() const{
    return value;
}
void BigInt::set_value(const std::string& str) {
    value = str;
}
const bool BigInt::get_sign() const{
    return sign;
}
void BigInt::set_sign(const bool s) {
    sign = s;
}


//operators
BigInt BigInt::operator=(const BigInt& other) {
    if (this != &other) {
        value = other.value;
        sign = other.sign;
    }
    return *this;
}
BigInt BigInt::operator=( short num){
    *this = BigInt(num);
    return *this;
}
BigInt BigInt::operator=( char num){
    *this = BigInt(num);
    return *this;
}
BigInt BigInt::operator=( int num){
    *this = BigInt(num);
    return *this;
}
BigInt BigInt::operator=( long num){
    *this = BigInt(num);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == false) out << '-';
    out << num.value;
    return out;
}
std::istream& operator>>(std::istream& in, BigInt& num){
    std::string input;
    in >> input;
    if (input[0] == '-') {num.sign = false; num.value = input.substr(1);}
    else {num.sign = true; num.value = input;}
    return in;
}
 
BigInt operator+(const BigInt& left, const BigInt& right) {
    if (left.sign == right.sign) {
        return BigInt(left.sign, stringSum(left.value, right.value));
    } 
    if (left.sign){
        if(firstBigger(left.value, right.value)){
            return BigInt(true, stringDif(left.value, right.value));
        } 
        return BigInt(false, stringDif(right.value, left.value));
    } else {
        if(firstBigger(right.value, left.value)){
            return BigInt(true, stringDif(right.value, left.value));
        } 
        return BigInt(false, stringDif(left.value, right.value));
    }
}
BigInt operator-(const BigInt& left, const BigInt& right){
    return left + BigInt(!right.sign, right.value);
}
BigInt operator*(const BigInt& left, const BigInt& right) {
    if (left.sign == right.sign)
        return BigInt(true, stringMultiply(left.value, right.value));
    else
        return BigInt(false, stringMultiply(left.value, right.value));
}
BigInt operator/(const BigInt& left, const BigInt& right) {
        if (left.sign == right.sign)
        return BigInt(true, quotientDivision(left.value, right.value));
    else
        return BigInt(false, quotientDivision(left.value, right.value));
}
BigInt operator%(const BigInt& left, const BigInt& right) {
        if (left.sign)
        return BigInt(true, remainderDivision(left.value, right.value));
    else
        return BigInt(false, remainderDivision(left.value, right.value));
}

BigInt BigInt::operator-(){                         //unary minus
    BigInt a;
    a.value = value;
    a.sign = !sign;
    return a;
}

//++++++++++++++
BigInt operator+(int left, const BigInt& right)  {return BigInt(left) + right;}
BigInt operator+(std::string left, const BigInt& right) {return BigInt(left) + right;}
BigInt operator+(short left, const BigInt& right) {return BigInt(left) + right;}
BigInt operator+(long left, const BigInt& right) {return BigInt(left) + right;}
BigInt operator+(char left, const BigInt& right) {return BigInt(left) + right;}
BigInt operator+(const BigInt& left, int right) {return left + BigInt(right);}
BigInt operator+(const BigInt& left, std::string right){return left + BigInt(right);}
BigInt operator+(const BigInt& left, long right){return left + BigInt(right);}
BigInt operator+(const BigInt& left, short right){return left + BigInt(right);}
BigInt operator+(const BigInt& left, char right){return left + BigInt(right);}


//-------------
BigInt operator-(int left, const BigInt& right)  {return BigInt(left) - right;}
BigInt operator-(std::string left, const BigInt& right) {return BigInt(left) - right;}
BigInt operator-(short left, const BigInt& right) {return BigInt(left) - right;}
BigInt operator-(long left, const BigInt& right) {return BigInt(left) - right;}
BigInt operator-(char left, const BigInt& right) {return BigInt(left) - right;}
BigInt operator-(const BigInt& left, int right) {return left - BigInt(right);}
BigInt operator-(const BigInt& left, std::string right){return left - BigInt(right);}
BigInt operator-(const BigInt& left, long right){return left - BigInt(right);}
BigInt operator-(const BigInt& left, short right){return left - BigInt(right);}
BigInt operator-(const BigInt& left, char right){return left - BigInt(right);}

//*****************
BigInt operator*(int left, const BigInt& right)  {return BigInt(left) * right;}
BigInt operator*(std::string left, const BigInt& right) {return BigInt(left) * right;}
BigInt operator*(short left, const BigInt& right) {return BigInt(left) * right;}
BigInt operator*(long left, const BigInt& right) {return BigInt(left) * right;}
BigInt operator*(char left, const BigInt& right) {return BigInt(left) * right;}
BigInt operator*(const BigInt& left, int right) {return left * BigInt(right);}
BigInt operator*(const BigInt& left, std::string right){return left * BigInt(right);}
BigInt operator*(const BigInt& left, long right){return left * BigInt(right);}
BigInt operator*(const BigInt& left, short right){return left * BigInt(right);}
BigInt operator*(const BigInt& left, char right){return left * BigInt(right);}

///////////////////
BigInt operator/(int left, const BigInt& right)  {return BigInt(left) / right;}
BigInt operator/(std::string left, const BigInt& right) {return BigInt(left) / right;}
BigInt operator/(short left, const BigInt& right) {return BigInt(left) / right;}
BigInt operator/(long left, const BigInt& right) {return BigInt(left) / right;}
BigInt operator/(char left, const BigInt& right) {return BigInt(left) / right;}
BigInt operator/(const BigInt& left, int right) {return left / BigInt(right);}
BigInt operator/(const BigInt& left, std::string right){return left / BigInt(right);}
BigInt operator/(const BigInt& left, long right){return left / BigInt(right);}
BigInt operator/(const BigInt& left, short right){return left / BigInt(right);}
BigInt operator/(const BigInt& left, char right){return left / BigInt(right);}

//%%%%%%%%%%%%%%%
BigInt operator%(int left, const BigInt& right)  {return BigInt(left) % right;}
BigInt operator%(std::string left, const BigInt& right) {return BigInt(left) % right;}
BigInt operator%(short left, const BigInt& right) {return BigInt(left) % right;}
BigInt operator%(long left, const BigInt& right) {return BigInt(left) % right;}
BigInt operator%(char left, const BigInt& right) {return BigInt(left) % right;}
BigInt operator%(const BigInt& left, int right) {return left % BigInt(right);}
BigInt operator%(const BigInt& left, std::string right){return left % BigInt(right);}
BigInt operator%(const BigInt& left, long right){return left % BigInt(right);}
BigInt operator%(const BigInt& left, short right){return left % BigInt(right);}
BigInt operator%(const BigInt& left, char right){return left % BigInt(right);}


//to other types
BigInt::operator std::string() const {              
    return (sign ? "" : "-") + value;
}                                                   
BigInt::operator int() const {
    return (sign ? 1 : -1) * std::atoi(value.c_str());
}
BigInt::operator short() const {
    return (sign ? 1 : -1) * std::atoi(value.c_str());
}
BigInt::operator char() const {
    return (sign ? 1 : -1) * std::atoi(value.c_str());
}
BigInt::operator long() const {
    return (sign ? 1 : -1) * std::atol(value.c_str());
}
