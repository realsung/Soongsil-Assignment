int main(){
    int *a;
    int **b;
    &a + *b;
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/8.c                                   1 ↵ root@vultr
test/8.c: In function ‘main’:
test/8.c:4:13: warning: initialization of ‘int’ from ‘int **’ makes integer from pointer without a cast [-Wint-conversion]
    4 |     int c = &a + *b;
      |             ^
*/