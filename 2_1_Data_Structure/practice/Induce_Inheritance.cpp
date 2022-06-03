#include <iostream>
#include <cstring>

using namespace std;

class SoBase{
private:
    int num;
public:
    SoBase() : num(20){
        cout << "SoBase()" << endl;
    }
    SoBase(int n) : num(n){
        cout << "SoBase(int n)" << endl;
    }
    void Show(){
        cout << num << endl;
    }
};

class SoDerived: public SoBase{ // 파생
private:
    int Derivednum;
public:
    SoDerived(): Derivednum(30){
        cout << "SoDerived()" << endl;
    }
    SoDerived(int n) : Derivednum(n){
        cout << "SoDerived(int n)" << endl;
    }
    SoDerived(int n1, int n2) : SoBase(n1), Derivednum(n2){
        cout << "SoDerived(int n1, int n2)" << endl;
    }
    void Show2(){
        Show();
        cout << "soDerived num : " << Derivednum << endl;
    }
};

int main(){
    SoDerived d1;
    d1.Show2();
    cout << "-------------------" << endl;
    SoDerived d2(12);
    d2.Show2();
    cout << "-------------------" << endl;
    SoDerived d3(23, 24);
    d3.Show2();
    cout << "-------------------" << endl;
}