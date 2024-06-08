struct Example {
    void x;
};
int main() {
    return 0;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/47.c                                  1 ↵ root@vultr
test/47.c:3:10: error: variable or field ‘x’ declared void
    3 |     void x; // Error: illegal type in struct or union field
      |          ^
*/