int main() {
    int array[-1];
    return 0;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/45.c                                  1 ↵ root@vultr
test/45.c: In function ‘main’:
test/45.c:2:9: error: size of array ‘array’ is negative
    2 |     int array[-1]; // Error: illegal array size of type
      |         ^~~~~
*/