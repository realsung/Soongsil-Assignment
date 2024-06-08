int main(){
    1.1 = 1; // l-value에는 변수만 ?
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/24.c                                      root@vultr
test/24.c: In function ‘main’:
test/24.c:4:9: error: lvalue required as left operand of assignment
    4 |     1.1 = 1; // l-value에는 변수만 ?
      |         ^
*/