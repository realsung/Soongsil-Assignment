int main(){
    int a = 1337;
    switch(a){
        case 1.1: break;
    }
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/21.c                                      root@vultr
test/21.c: In function ‘main’:
test/21.c:5:9: error: case label does not reduce to an integer constant
    5 |         case 1.1: break; // integer constant가 아닌경우
      |         ^~~~
*/