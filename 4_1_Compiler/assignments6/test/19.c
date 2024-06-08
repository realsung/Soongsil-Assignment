int main(){
    int *a;
    float b;
    a = &b;
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/19.c                                      root@vultr
test/19.c: In function ‘main’:
test/19.c:5:7: warning: assignment to ‘int *’ from incompatible pointer type ‘float *’ [-Wincompatible-pointer-types]
    5 |     a = &b;
      |       ^
*/