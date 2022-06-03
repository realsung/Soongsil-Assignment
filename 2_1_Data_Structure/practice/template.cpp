#include <iostream>

using namespace std;

// template <typename T>
// template <class T>
template <class T1, class T2>

void ShowData(double num){
    cout << (T1)num << ", " << (T2)num << endl;
}

// T Add(T num1, T num2){
//     return num1 + num2;
// }


int main(){
    // cout << Add<int>(1, 2) << endl;
    // cout << Add<double>(1.2, 2.2) << endl;
    ShowData<char, int>(65);
}