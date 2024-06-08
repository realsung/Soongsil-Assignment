int main() {
    int x;
    x = (char *)5;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/37.c                                      root@vultr
test/37.c: In function ‘main’:
test/37.c:2:13: warning: initialization of ‘int’ from ‘char *’ makes integer from pointer without a cast [-Wint-conversion]
    2 |     int x = (char *)5; // Error: not permitted type casting in expression
      |             ^
*/