#include <iostream>

using namespace std;

int AAA(int a, int b){
    cout << "void AAA(int a, int b)" << endl;
    return a + b;
}

void AAA(int a){
    cout << "void AAA(int a)" << endl;
}

void AAA(){
    cout << "void AAA()" << endl;
}

int main(){
    cout << AAA(1,2) << endl;
    AAA();
    AAA(5);
}