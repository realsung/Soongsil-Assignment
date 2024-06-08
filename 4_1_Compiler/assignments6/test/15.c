int main(){
    5 / 1.1;
    10 / 0;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # g++ -fsyntax-only test/51.c                                      root@vultr
test/51.c: In function ‘int main()’:
test/51.c:3:8: warning: division by zero [-Wdiv-by-zero]
    3 |     10 / 0;
      |     ~~~^~~
*/