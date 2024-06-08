int f(int, int, int);

int main(){
    f(1, 2);
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/14.c                                  1 ↵ root@vultr
test/14.c: In function ‘main’:
test/14.c:4:13: error: too few arguments to function ‘f’
    4 |     int d = f(1, 2);
      |             ^
test/14.c:1:5: note: declared here
    1 | int f(int, int, int);
      |     ^
*/