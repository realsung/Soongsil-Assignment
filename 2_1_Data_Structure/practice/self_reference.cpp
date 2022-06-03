#include <iostream>

using namespace std;

class SelfRef{
private:
    int num;
public:
    SelfRef(int n) : num(n){
        cout << "Create Object" << endl;
    }
    SelfRef& Adder(int n){
        num += n;
        return *this;
    }
    SelfRef& Show(){
        cout << num << endl;
        return *this;
    }
};

class SelfRef2{
private:
    int num;
public:
    SelfRef2(int n) : num(n){
        cout << "Create Object" << endl;
    }
    SelfRef2 Adder(int n){
        num += n;
        return *this;
    }
    SelfRef2 Show(){
        cout << num << endl;
        return *this;
    }
};

int main(){
    SelfRef obj(3);
    SelfRef &ref = obj.Adder(2);
    obj.Show();
    ref.Show();
    obj.Adder(1).Show().Adder(2).Show();
    ref.Adder(1).Show().Adder(2).Show();

    SelfRef2 obj2(3);
    obj2.Adder(3);
    obj2.Show();
    obj2.Adder(1).Show().Adder(2).Show();
}