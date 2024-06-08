struct s { int a; struct s b; int c; } d; 
int main(){
}

// gcc 결과
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/1.c
test/1.c:2:28: error: field ‘b’ has incomplete type
    2 | struct s { int a; struct s b; int c; } d;
      |                            ^
-------------------------------------------------
*/