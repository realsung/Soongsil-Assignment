#include <iostream>
#include <cstring>

using namespace std;

class Person{
private:
    char *name;
    int age;
public:
    Person(char *myname, int age){
        int len = strlen(myname) + 1;
        name = new char[len];
        strcpy(name, myname);
        this->age = age;
    }
    Person(const Person& copy): age(copy.age){
        int len = strlen(copy.name) + 1;
        name = new char[len];
        strcpy(name, copy.name);
    }
    ~Person(){
        delete []name;
    }
    void Show(){
        cout << name << " : " << age << endl;
    }
};

int main(){
    char name[] = "SungJun";
    Person man1(name, 21);
    Person man2 = man1;
    man1.Show();
    man2.Show();
}