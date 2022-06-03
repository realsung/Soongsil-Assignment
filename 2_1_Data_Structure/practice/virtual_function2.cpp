#include <iostream>

using namespace std;

class First{
public:
    void FirstFunc(){
        cout << "First Function()" << endl;
    }
    void myFunc(){
        cout << "FirstFunc()" << endl;
    }
    virtual void myFunc2(){
        cout << "FirstFunc()" << endl;
    }
};

class Second: public First{
public:
    void SecondFunc(){
        cout << "Second Function()" << endl;
    }
    void myFunc(){
        cout << "SecondFunc()" << endl;
    }
    virtual void myFunc2(){
        cout << "SecondFunc()" << endl;
    }
};

class Third: public Second{
public:
    void ThirdFunc(){
        cout << "Third Function()" << endl;
    }
    void myFunc(){
        cout << "ThirdFunc()" << endl;
    }
    virtual void myFunc2(){
        cout << "ThirdFunc()" << endl;
    }
};

int main(){
    Third *tptr = new Third();
    Second *sptr = tptr;
    First *fptr = sptr;
    
    tptr->FirstFunc();
    tptr->SecondFunc();
    tptr->ThirdFunc();

    sptr->FirstFunc();
    sptr->SecondFunc();
    // sptr->ThirdFunc(); // error

    fptr->FirstFunc();
    // fptr->SecondFunc(); // error
    // fptr->ThirdFunc(); // error

    tptr->myFunc();
    sptr->myFunc();
    fptr->myFunc();

    fptr->myFunc2();
    sptr->myFunc2();
    tptr->myFunc2();
}