#include <iostream>

using namespace std;

inline int sqrt_(int x){
    return x*x;
}

int main(){
    cout << sqrt_(5) << endl;
    cout << sqrt_(10) << endl;
    return 0;
}