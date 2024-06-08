int f(int a){
    return 0;
}
int main(){
    f(1, 2);
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/13.c                                  1 ↵ root@vultr
test/13.c: In function ‘main’:
test/13.c:6:13: error: too many arguments to function ‘f’
    6 |     int d = f(1, 2);
      |             ^
test/13.c:1:5: note: declared here
    1 | int f(int a){
      |     ^
*/