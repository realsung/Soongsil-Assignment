enum P{
    A = 1,
    B = 2,
    C = "123"
};

int main(){
    enum P p;
    p = A;
    p = B;
    p = C;
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/27.c                                  1 ↵ root@vultr
test/27.c:4:9: error: enumerator value for ‘C’ is not an integer constant
    4 |     C = "123"
      |         ^~~~~
*/