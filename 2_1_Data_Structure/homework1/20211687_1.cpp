#include <iostream>

void divide(const int num1, const int num2, int &q, int &r){
    if(num2 == 0) throw "Zero Division Error";
    q = num1 / num2;
    r = num1 % num2;
}

int main(){
    int num1, num2, q, r;
    std::cin >> num1 >> num2;
    try{
        divide(num1, num2, q, r);
        std::cout << num1 << " / " << num2 << " = " << q << ", ";
        std::cout << num1 << " % " << num2 << " = " << r << "\n";
    }catch(const char *s){
        std::cout << s << "\n";
    }
}