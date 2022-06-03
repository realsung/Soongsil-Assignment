#include <iostream>

using namespace std;

namespace A{
    void A(){
        cout << "Namespace A::A()" << endl;
    }
    void B(){
        cout << "Namespace A::B()" << endl;
    }
    namespace C{
        int c = 10;
        void C(){
            cout << "Namespace A::C::C()" << endl;
        }
    }
}

namespace ABC = A::C;
int global = 50;

int main(){
    A::A();
    A::B();
    A::C::C();
    cout << A::C::c << endl;
    ABC::c = 20;
    cout << A::C::c << endl;
    cout << ::global << endl;
}