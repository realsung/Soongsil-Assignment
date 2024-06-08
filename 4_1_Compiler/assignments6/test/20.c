void foo() {
    return 1;
}
int main() {
    foo();
    return main;
}
/*
test/48.c: In function ‘foo’:
test/48.c:3:12: warning: ‘return’ with a value, in function returning void
    3 |     return 1; // Error: invalid function return type
      |            ^
test/48.c:2:6: note: declared here
    2 | void foo() {
      |      ^~~
-------------------
*/