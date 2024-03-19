#include <stdio.h>
#include <stdlib.h>

/*
1장에서 설명한 LR Parsing 방식을 이용하여 수식의 값을 계산하는 프로그램을 완성하고 실험하시오.
과제-1과 마찬가지로 수식은 +,*,(,), 정수 및 실수 들로 구성된다.  수식이 올바로 처리되는지 충분히 많은 다양한 종류의 수식을 실험해야 합니다. 잘못된 수식인 경우는 오류메시지를 출력하도록 합니다. 보고서에는 과제의 내용과 해결방법, 결론 외에 프로그램 실행결과(스크린샷), 원시프로그램을 수록하여 한개의 화일(한글, 워드 혹은 pdf 화일)로 압축하지 말고 제출합니다.   
*/

#define NUMBER 256
#define PLUS 257
#define STAR 258
#define LPAREN 259
#define RPAREN 260
#define END 261
#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define ACC 999

int yyparse();
void push(int l);
void shift(int l);
void reduce(int l);
void yyerror();
int yylex();

int action[12][6] = {
    {5, 0, 0, 4, 0, 0}, {0, 6, 0, 0, 0, ACC}, {0, -2, 7, 0, -2 -2},
    {0, -4, -4, 0, -4, -4}, {5, 0, 0, 4, 0, 0}, {0, -6, -6, 0, -6, -6},
    {5, 0, 0, 4, 0, 0}, {5, 0, 0, 4, 0, 0}, {0, 6, 0, 0, 11, 0},
    {0, -1, 7, 0, -1, -1}, {0, -3, -3, 0, -3, -3}, {0, -5, -5, 0, -5, -5}
};

int go_to[12][3] = {
    {1, 2, 3}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {8, 2, 3}, {0, 0, 0},
    {0, 9, 3}, {0, 0, 10}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};

int prod_left[7] = {0, EXPRESSION, EXPRESSION, TERM, TERM, FACTOR, FACTOR};
int prod_length[7] = {0, 3, 1, 3, 1, 3, 1};

int stack[1000];
int top = -1;
int sym;

int main(){
    yyparse();
}

int yyparse(){
    int i;
    stack[++top] = 0;
    sym = yylex();
    do{
        i = action[stack[top]][sym-256];
        if(i == ACC){
            printf("success!\n");
        }else if(i > 0){
            shift(i);
        }else if(i < 0){
            reduce(-i);
        }else{
            yyerror();
            return 1;
        }
    }while(i != ACC);
}

void push(int l){
    stack[++top] = l;
}

void shift(int l){
    push(l);
    
    sym = yylex();
}

void reduce(int l){
    int old_top;
    top -= prod_length[l];
    old_top = top;
    push(go_to[stack[old_top]][prod_left[l]]);
}

void yyerror(){
    printf("syntax error\n");
    exit(1);
}

int yylex(){
    static char ch = ' ';
    int i;
    while(ch == ' ' || ch == '\t' || ch == '\n'){
        ch = getchar();
    }
    if(ch == '+'){
        ch = getchar();
        return PLUS;
    }else if(ch == '*'){
        ch = getchar();
        return STAR;
    }else if(ch == '('){
        ch = getchar();
        return LPAREN;
    }else if(ch == ')'){
        ch = getchar();
        return RPAREN;
    }else if(ch == '\n'){
        return END;
    }else if(ch == EOF){
        return END;
    }else if(ch >= '0' && ch <= '9'){
        i = 0;
        do{
            i = i*10 + ch - '0';
            ch = getchar();
        }while(ch >= '0' && ch <= '9');
        return NUMBER;
    }else{
        printf("lexical error\n");
        exit(1);
    }
}