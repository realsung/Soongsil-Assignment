#include <iostream>
#include <cstring>

using namespace std;

class Person{
private:
    int age;
    char name[50];
public:
    Person(int myage, char *myname) : age(myage){
        strcpy(name, myname);
    }
    void ShowName() const{
        cout << "Name : " << name << endl;
    }
    void ShowOld() const{
        cout << "Age : " << age << endl;
    }
};

class UnivStudent: public Person{
private:
    char major[50];
public:
    UnivStudent(char *myname, int myage, char *mymajor) : Person(myage, myname){
        strcpy(major, mymajor);
    }
    void Info() const{
        ShowName();
        ShowOld();
        cout << "Major : "  << major << endl;
    }
};

int main(){
    UnivStudent sung("SungJun", 21, "Math");
    sung.Info();
    UnivStudent *ptr = new UnivStudent("Lee", 22, "English");
    ptr->Info();
}