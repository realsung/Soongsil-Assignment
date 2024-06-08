// 더 작은 자료형에 더 큰 자료형을 대입하는 경우
// --- warning at line 6:incompatible types in assignment expression (case 11)
int main(){
    float a;
    int b;
    a = 1.1;
    b = a;
}

// gcc 결과
/*
gcc -o ./test2 ./test/2.c
gcc -fsyntax-only test/2.c
아무것도 안뜸
*/