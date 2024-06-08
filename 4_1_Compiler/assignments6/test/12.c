int main(){
    int a;
    int b;
    b = a[10];
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/12.c                                      root@vultr
test/12.c: In function ‘main’:
test/12.c:3:14: error: subscripted value is neither array nor pointer nor vector
    3 |     int b = a[10];
      |              ^
*/