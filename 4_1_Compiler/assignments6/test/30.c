void foo(int x);
int main() {
    char *str;
    foo(str);
}
/*
test/30.c: In function ‘main’:
test/30.c:9:9: warning: passing argument 1 of ‘foo’ makes integer from pointer without a cast [-Wint-conversion]
    9 |     foo(str);
      |         ^~~
      |         |
      |         char *
test/30.c:4:14: note: expected ‘int’ but argument is of type ‘char *’
    4 | void foo(int x) {
      |          ~~~~^
*/