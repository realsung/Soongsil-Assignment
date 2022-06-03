#include <iostream>

using namespace std;

int main(){
    int a = 30;
    int &b = a;
    b = 40;
    cout << b;
}