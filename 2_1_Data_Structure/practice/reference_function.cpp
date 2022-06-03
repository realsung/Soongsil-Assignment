#include <iostream>

using namespace std;

int& A(int &ref){
    ref++;
    return ref;
}

int B(int &ref){
    ref++;
    return ref;
}


int main(){
    int a = 1;
    int &b = A(a);
    a++;
    cout << "a : " << a << ", b : " << b << endl;
    b++;
    cout << "a : " << a << ", b : " << b << endl;

    int c = 1;
    int d = A(c);
    c += 1;
    cout << "c : " << c << ", d : " << d << endl;
    d += 2;
    cout << "c : " << c << ", d : " << d << endl;

    // ===========================================

    int e = 1;
    int f = B(e);
    e += 1;
    cout << "e : " << e << ", f : " << f << endl;
    f += 2;
    cout << "e : " << e << ", f : " << f << endl;

    // ERROR case
    // int g = 1;
    // int &h = B(g); <- B() return -> not reference
    
}