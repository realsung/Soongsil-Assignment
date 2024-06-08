int f(char *);
int main(){
    int a;
    f(a);
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/22.c
test/22.c: In function ‘main’:
test/22.c:6:7: warning: passing argument 1 of ‘f’ makes pointer from integer without a cast [-Wint-conversion]
    6 |     f(a);
      |       ^
      |       |
      |       int
test/22.c:2:7: note: expected ‘char *’ but argument is of type ‘int’
    2 | int f(char *);
      |       ^~~~~~
*/