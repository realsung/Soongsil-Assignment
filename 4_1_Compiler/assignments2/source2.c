/*
1장에서 설명한 LR Parsing 방식을 이용하여 수식의 값을 계산하는 프로그램을 완성하고 실험하시오.
과제-1과 마찬가지로 수식은 +,*,(,), 정수 및 실수 들로 구성된다. 수식이 올바로 처리되는지 충분히 많은 다양한 종류의 수식을 실험해야 합니다. 잘못된 수식인 경우는 오류메시지를 출력하도록 합니다. 보고서에는 과제의 내용과 해결방법, 결론 외에 프로그램 실행결과(스크린샷), 원시프로그램을 수록하여 한개의 화일(한글, 워드 혹은 pdf 화일)로 압축하지 말고 제출합니다.   
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG 0
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

typedef enum {INT, FLT} kind;

struct num_struct {
    kind t;
    union {
        int i;
        float f;
    } val;
};

int yyparse();
void push(int l);
void shift(int l);
void reduce(int l);
void yyerror();
int yylex();
void lex_error();

int action[12][6] = {
    {5, 0, 0, 4, 0, 0}, {0, 6, 0, 0, 0, ACC}, {0, -2, 7, 0, -2, -2},
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

int stack[1000] = {0, };
int top = -1;
int sym;

char yytext[32];
struct num_struct yylval;
struct num_struct value[1000];

int main(){
    yyparse();
    return 0;
}

int yyparse(){
    int i;
    stack[++top] = 0;
    sym = yylex();
#if DEBUG
    printf("[DEBUG] sym: %d\n", sym);
#endif
    do {
        i = action[stack[top]][sym - 256];
#if DEBUG
        printf("[DEBUG] i: %d\n", i);
#endif
        if (i == ACC) {
            printf("Success!\n");
            if (value[1].t == INT) {
                printf("Result: %d\n", value[1].val.i);
            } else {
                printf("Result: %f\n", value[1].val.f);
            }
        } else if (i > 0) {
            shift(i);
        } else if (i < 0) {
            reduce(-i);
        } else {
            yyerror();
            return 1;
        }
    } while (i != ACC);
    return 0;
}

void push(int l){
    stack[++top] = l;
}

void shift(int l){
    push(l);
    value[top] = yylval;
    sym = yylex();
#if DEBUG
    printf("[DEBUG] sym: %d\n", sym);
#endif
}

void reduce(int l){
#if DEBUG
    printf("[DEBUG] reduce(%d)\n", l);
#endif
    int old_top;
    top -= prod_length[l];
    old_top = top;
    push(go_to[stack[old_top]][prod_left[l]]);

    switch(l){
        case 1: // E -> E + T
            if (value[old_top + 1].t == INT && value[old_top + 3].t == INT) {
                value[top].t = INT;
                value[top].val.i = value[old_top + 1].val.i + value[old_top + 3].val.i;
            }else if(value[old_top + 1].t == INT && value[old_top + 3].t == FLT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.i + value[old_top + 3].val.f;
            }else if(value[old_top + 1].t == FLT && value[old_top + 3].t == INT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.f + value[old_top + 3].val.i;
            }
            else if(value[old_top + 1].t == FLT && value[old_top + 3].t == FLT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.f + value[old_top + 3].val.f;
            }
            break;
        case 2: // E -> T
            value[top] = value[old_top + 1];
            break;
        case 3: // T -> T * F
            if (value[old_top + 1].t == INT && value[old_top + 3].t == INT) {
                value[top].t = INT;
                value[top].val.i = value[old_top + 1].val.i * value[old_top + 3].val.i;
            }else if(value[old_top + 1].t == INT && value[old_top + 3].t == FLT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.i * value[old_top + 3].val.f;
            }else if(value[old_top + 1].t == FLT && value[old_top + 3].t == INT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.f * value[old_top + 3].val.i;
            }
            else if(value[old_top + 1].t == FLT && value[old_top + 3].t == FLT) {
                value[top].t = FLT;
                value[top].val.f = value[old_top + 1].val.f * value[old_top + 3].val.f;
            }
            break;
        case 4: // T -> F
            value[top] = value[old_top + 1];
            break;
        case 5: // F -> (E)
            value[top] = value[old_top + 2];
            break;
        case 6: // F -> number
            value[top] = value[old_top + 1];
            break;
        default:
            lex_error();
            break;
    }
}

void yyerror(){
    printf("Syntax error\n");
    exit(1);
}

int yylex(){
    static char ch = ' ';
    int i = 0;
    float f = 0.0, div = 10.0;
    while(ch == ' ' || ch == '\t'){
        ch = getchar();
    }
    if(ch == '+'){
        ch = getchar();
        return PLUS;
    } else if(ch == '*'){
        ch = getchar();
        return STAR;
    } else if(ch == '('){
        ch = getchar();
        return LPAREN;
    } else if(ch == ')'){
        ch = getchar();
        return RPAREN;
    } else if(ch == '\n' || ch == EOF){
        return END;
    } else if(isdigit(ch) || ch == '.'){
        yylval.t = INT;
        do {
            if(ch == '.') {
                yylval.t = FLT;
            } else if(yylval.t == INT) {
                i = i * 10 + (ch - '0');
            } else {
                f += (float)(ch - '0') / div;
                div *= 10.0;
            }
            ch = getchar();
        } while(isdigit(ch) || (yylval.t == INT && ch == '.'));

        if(yylval.t == INT) {
            yylval.val.i = i;
        } else {
            yylval.val.f = i + f;
        }
        return NUMBER;
    } else {
        lex_error();
    }
    return 0;
}

void lex_error(){
    printf("Lexical error\n");
    exit(1);
}
