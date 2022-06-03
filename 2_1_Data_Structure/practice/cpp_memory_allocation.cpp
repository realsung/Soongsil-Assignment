#include <iostream>

using namespace std;

int main(){
    int *a = new int;
    double *b = new double;
    int *c = new int[3];
    double *d = new double[5];
    delete a;
    delete b;
    delete []c;
}