#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <termio.h>

#define SIZE 4

uint8_t puzzle[SIZE][SIZE] = {};

void init();
void game();
void static_setup();
void dynamic_setup();
void printPuzzle();
_Bool isCorrect();
int getch(void);

int main(int argc, char *argv[]){
    uint8_t mode;
    if(argc != 2){
        printf("Using %s [Mode]\n",argv[0]);
        return 0;
    }
    init();
    mode = atoi(argv[1]);
    if(mode == 1){
        system("clear");
        static_setup();
        game();
    }else if(mode == 2){
        system("clear");
        dynamic_setup();
        game();
    }else{
        puts("Mode를 잘못 선택함");
    }
}

void init(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    srand(time(NULL));
}

void game(){
    uint8_t i,j,tmp,curX,curY,move=0;
    int8_t ch;

    while(1){
        for(i=0; i<SIZE; i++){
            for(j=0; j<SIZE; j++){
                if(puzzle[i][j] == 0){
                    curX = i;
                    curY = j;
                    break;
                }
            }
        }
        system("clear");
        printPuzzle();
        ch = getch();
        switch(ch){
            case 27:
                exit(0);
            
            case 'i':
            case 'I':
                if(curX < 3){
                    tmp = puzzle[curX][curY];
                    puzzle[curX][curY] = puzzle[curX+1][curY];
                    puzzle[curX+1][curY] = tmp;
                    move++;
                    // printf("curX : %d, curY : %d\n",curX,curY);
                }
                break;

            case 'j':
            case 'J':
                if(curY < 3){
                    tmp = puzzle[curX][curY];
                    puzzle[curX][curY] = puzzle[curX][curY+1];
                    puzzle[curX][curY+1] = tmp;
                    move++;
                    // printf("curX : %d, curY : %d\n",curX,curY);
                }
                break;

            case 'k':
            case 'K':
                if(curX >= 1){
                    tmp = puzzle[curX][curY];
                    puzzle[curX][curY] = puzzle[curX-1][curY];
                    puzzle[curX-1][curY] = tmp;
                    move++;
                    // printf("curX : %d, curY : %d\n",curX,curY);
                }
                break;

            case 'l':
            case 'L':
                if(curY >= 1){
                    tmp = puzzle[curX][curY];
                    puzzle[curX][curY] = puzzle[curX][curY-1];
                    puzzle[curX][curY-1] = tmp;
                    move++;
                    // printf("curX : %d, curY : %d\n",curX,curY);
                }
                break;
            default:
                puts("\tTry Again :)\n");
                break;
        }
        if(isCorrect() && move >= 1){
            system("clear");
            printPuzzle();
            printf("\t축하합니다\n");
            sleep(3);
            exit(0);
        }
    }
}

void static_setup(){
    uint8_t i,j,chk=1;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            puzzle[i][j] = chk++;
        }
    }
    puzzle[SIZE-1][SIZE-1] = 0;
}

void dynamic_setup(){
    uint8_t idx1_1,idx1_2,idx2_1,idx2_2,i,j,tmp,curX,curY;
    static_setup();
    for(i=0; i<rand()%0x1337; i++){
        idx1_1 = rand() % 4;
        idx1_2 = rand() % 4;
        idx2_1 = rand() % 4;
        idx2_2 = rand() % 4;
        tmp = puzzle[idx1_1][idx1_2];
        puzzle[idx1_1][idx1_2] = puzzle[idx2_1][idx2_2];
        puzzle[idx2_1][idx2_2] = tmp;
    }
    if(puzzle[SIZE-1][SIZE-1] != 0){
        for(i=0; i<SIZE; i++){
            for(j=0; j<SIZE; j++){
                if(puzzle[i][j] == 0){
                    curX = i;
                    curY = j;
                    break;
                }
            }
        }
        tmp = puzzle[SIZE-1][SIZE-1];
        puzzle[SIZE-1][SIZE-1] = puzzle[curX][curY];
        puzzle[curX][curY] = tmp;
    }
}

void printPuzzle(){
    uint8_t i,j;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if(puzzle[i][j] == 0){
                printf(" \t");
            }else{
                printf("%d\t",puzzle[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

_Bool isCorrect(){
    uint8_t i,j, cnt=1, flag=0;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if(cnt == 16){
                return 1;
            }
            if(puzzle[i][j] == cnt){
                cnt++;
            }else{
                return 0;
            }
        }
    }
    return 1;
}

int getch(void) {
    int ch;
    struct termios buf;
    struct termios save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch=getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}