#include <iostream>
#include <cstring>

using namespace std;

struct Car{
    char name[10];
    int speed;

    void print_speed(){
        cout << "speed : " << speed << endl;
    }

    void print_name();
};

int main(){
    Car a;
    a.speed = 10;
    strcpy(a.name, "asd");
    a.print_speed();
    a.print_name();

    Car b = {"ABC", 20};
    b.print_speed();
    b.print_name();
}

void Car::print_name(){
    cout << "name : " << name << endl;
}