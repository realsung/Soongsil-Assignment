#include <iostream>

using namespace std;

class A{
private:
    int num;
public:
    A(){
        cout << "Call A() Constructor" << endl;
    }
    A(int n) : num(n){
        cout << "Call A(int n) : num(n) Constructor" << endl;
    }
    A& Add(int n){
        num += n;
        return *this;
    }
    void B(){
        cout << "Call B() & num : " << num << endl;
    }
    void B() const{
        cout << "Call const B() & num : " << num << endl;
    }
};

int main(){
    A a(1);
    const A b(1);
    a.B();
    b.B();
}