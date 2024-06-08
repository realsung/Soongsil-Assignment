struct p{
    int a;
    int b;
};

int main(){
    struct p p1;
    p1.c;
}

/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/17.c                                      root@vultr
test/17.c: In function ‘main’:
test/17.c:12:7: error: ‘struct p’ has no member named ‘c’
   12 |     p1.c = 2;
      |       ^
*/