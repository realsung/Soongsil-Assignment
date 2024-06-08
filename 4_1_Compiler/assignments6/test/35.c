int main() {
    int x = 5;
    (x + 2) = 7;
    return 0;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/39.c                                      root@vultr
test/39.c: In function ‘main’:
test/39.c:4:13: error: lvalue required as left operand of assignment
    4 |     (x + 2) = 7; // Error: expression is not an lvalue
      |             ^
*/