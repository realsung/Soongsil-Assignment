int main() {
    char *str;
    -str;
    return 0;
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/28.c                                  1 ↵ root@vultr
test/28.c: In function ‘main’:
test/28.c:5:18: error: wrong type argument to unary minus
    5 |     int result = -str;
      |                  ^
*/