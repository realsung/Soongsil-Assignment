#include <iostream>

using namespace std;

int A(int a=0){
    return a+1;
}

int B(int a, int b, int c=1, int d=2){
    return a+b+c+d;
}

int main(){
    cout << A() << endl;
    cout << A(2) << endl;
    cout << B(3, 4) << endl;
    cout << B(3, 4, 5) << endl;
    cout << B(3, 4, 5, 6) << endl;
}