#include <iostream>
#include <cstring>

using namespace std;

class A{
private:
    int a;
    int b;
    char *name;

public:
    A();
    A(int n1, int n2, char *myname);
    ~A();
};

int main(){
    char n[] = "asdasd";
    A *a = new A(1, 2, n);
    delete a;

    A b = A(1, 2, n);

    // 객체 배열
    A arr[3];
    A *ptr = new A[3];
    delete []ptr;

    // 객체 포인터 배열
    A *ptr2[3];
    ptr2[0] = new A();
    ptr2[1] = new A();
    ptr2[2] = new A();
}

A::A(){
    cout << "Call Constructor A()" << endl;
    name = new char[20];
    strcpy(name, "person");
}

A::A(int n1, int n2, char *myname) : a(n1){ 
    cout << "Call Constructor A(int n1, int n2, char *myname)" << endl;
    b = n2;
    name = new char[strlen(myname) + 1];
    strcpy(name, myname);
}

A::~A(){
    cout << "Call Destructor" << endl;
    delete []name;
}