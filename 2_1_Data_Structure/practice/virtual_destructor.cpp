#include <iostream>

using namespace std;

class First{
public:
    First(){
        cout << "Construictor First()" << endl;
    }
    virtual ~First(){
        cout << "Desturcor ~First()" << endl;
    }
};

class Second: public First{
public:
    Second(){
        cout << "Construictor Second()" << endl;
    }
    virtual ~Second(){
        cout << "Desturcor ~Second()" << endl;
    }
};

class Third: public Second{
public:
    Third(){
        cout << "Construictor Third()" << endl;
    }
    virtual ~Third(){
        cout << "Desturcor ~Third()" << endl;
    }
};

int main(){
    First *ptr = new Third();
    delete ptr;
}