int main(){
    int a;
    int b;
    b(a);
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/7.c                                       root@vultr
test/7.c: In function ‘main’:
test/7.c:5:5: error: called object ‘b’ is not a function or function pointer
    5 |     b(a);
      |     ^
test/7.c:4:9: note: declared here
    4 |     int b;
      |         ^
-----------------------
*/