#include <iostream>

using namespace std;

class First{
public:
    void FirstFunc(){
        cout << "First()" << endl;
    }
    virtual void Test(){
        cout << "First Test()" << endl;
    }
};

class Second: public First{
public:
    void SecondFunc(){
        cout << "Second()" << endl;
    }
    virtual void Test(){
        cout << "Second Test()" << endl;
    }
};

class Third: public Second{
public:
    void ThirdFunc(){
        cout << "Third()" << endl;
    }
    virtual void Test(){
        cout << "Third Test()" << endl;
    }
};


int main(){
    Third obj;
    obj.FirstFunc();
    obj.SecondFunc();
    obj.ThirdFunc();
    obj.Test();

    Second &sref = obj;
    sref.FirstFunc();
    sref.SecondFunc();
    sref.Test();

    First &fref = obj;
    fref.FirstFunc();
    fref.Test();
}