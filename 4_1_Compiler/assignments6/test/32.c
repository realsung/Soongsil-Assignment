int main() {
    int array[5];
    int result;
    result = array;
    return 0;
}
/*
test/32.c: In function ‘main’:
test/32.c:3:18: warning: initialization of ‘int’ from ‘int *’ makes integer from pointer without a cast [-Wint-conversion]
    3 |     int result = array; // Error: scalar type expr required in expression
      |                  ^~~~~
*/