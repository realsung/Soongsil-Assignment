#include <iostream>

using namespace std;

class Base{
public:
    void BaseFunc(){
        cout << "Base Function()" << endl;
    }
};

class Derived: public Base{
public:
    void DerivedFunc(){
        cout << "Derived Function()" << endl;
    }
};

int main(){
    Base *ptr = new Derived();
    // ptr->DerivedFunc(); // error
    ptr->BaseFunc();

    Derived *ptr2 = new Derived();
    ptr2->BaseFunc();
    ptr2->DerivedFunc();
    Base *ptr3 = ptr2;

}