int main(){
    int *a;
    int b;
    a + b;
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/9.c                                       root@vultr
test/9.c: In function ‘main’:
test/9.c:4:13: warning: initialization of ‘int’ from ‘int *’ makes integer from pointer without a cast [-Wint-conversion]
    4 |     int c = a + b;
      |             ^
*/