// clang -o source source.c -O3
// 20211687 sungjun park
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

enum token {TOKEN_NULL, NUMBER, PLUS, STAR, LP, RP, END, DIVIDE} token;
typedef enum {INT, FLT} kind;
struct{
    kind t;
    union{
        int i;
        float f;
    }val;
} num;

void get_token();
float expression();
float term();
float factor();
void error(int i);

int main(){
    float result;
    get_token();
    result = expression();
    if(token != END){
        error(3);
    }else{
        if(num.t == INT){
            printf("result = %d\n", (int)result);
        }else if(num.t == FLT){
            printf("result = %f\n", result);
        }
    }
}

float expression(){
    float result;
    result = term();
    while(token == PLUS){
        get_token();
        result = result + term();
    }
#if DEBUG
    printf("[DEBUG] expression() : %f\n", result);
#endif
    return result;
}

float term() {
    float result;
    result = factor();
    while (token == STAR || token == DIVIDE) {
        if(token == STAR){
            get_token();
            result = result * factor();
        }else if(token == DIVIDE){
            get_token();
            float tmp = factor();
            if(tmp == 0){
                error(3);
            }
            result = result / factor();
        }
    }
#if DEBUG
    printf("[DEBUG] term() : %f\n", result);
#endif
    return result;
}

float factor(){
    float result;
    if(token == NUMBER){
        if(num.t == INT){
            result = num.val.i;
        }else if(num.t == FLT){
            result = num.val.f;
        }
        get_token();
    }else if(token == LP){
        get_token();
        result = expression();
        if(token == RP){
            get_token();
        }else{
            error(2);
        }
    }else{
        error(1);
    }
#if DEBUG
    printf("[DEBUG] factor() : %f\n", result);
#endif
    return result;
}

void get_token(){
    char ch;
    while((ch = getchar()) == ' ');
    if(ch >= '0' && ch <= '9'){
        num.t = INT;
        num.val.i = ch - '0';
        while((ch = getchar()) >= '0' && ch <= '9'){
            num.val.i = num.val.i * 10 + ch - '0';
        }
        token = NUMBER;
        if(ch == '.'){
            num.t = FLT;
            num.val.f = num.val.i;
            float f = 0.1;
            while((ch = getchar()) >= '0' && ch <= '9'){
                num.val.f = num.val.f + (ch - '0') * f;
                f = f * 0.1;
            }
        }
        ungetc(ch, stdin);
    }else if(ch == '+'){
        token = PLUS;
    }else if(ch == '*'){
        token = STAR;
    }else if(ch == '/'){
        token = DIVIDE;    
    }else if(ch == '('){
        token = LP;
    }else if(ch == ')'){
        token = RP;
    }else if(ch == '\n'){
        token = END;
    }else{
        error(1);
    }
}

void error(int i){
    switch(i){
        case 1:
            printf("error 1: ");
            break;
        case 2:
            printf("error 2: ");
            break;
        case 3:
            printf("error 3: ");
            break;
    }
    exit(1);
}

/*
1장에서 설명한 Recursive-Descent Parsing 방식을 이용하여 수식의 값을 계산하는 프로그램을 완성하고 실험하시오.

수식은 +,*,(,), 정수 및 실수 들로 구성된다.  보고서에는 과제의 내용과 해결방법, 결론 외에 프로그램 실행결과(스크린샷), 원시프로그램을 수록하여 한개의 화일(한글, 워드 혹은 pdf 화일)로 압축하지 말고 제출합니다.  

프로그램은 반드시 UNIX 환경(Linux, 혹은 cygwin도 좋겠음)에서 작성하고 실험하기 바랍니다. 질문이나 프로그램에 문제가 있어 도움이 필요하면 언제든 이메일, 문자, 전화, 혹은 zoom 으로 연락하기 바랍니다
*/