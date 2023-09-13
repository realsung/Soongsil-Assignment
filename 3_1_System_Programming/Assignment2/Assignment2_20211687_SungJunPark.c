#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define MENU_SIZE 5
#define NAME_SIZE 0x20
#define ORDER_SIZE 3

typedef struct{
    uint8_t name[NAME_SIZE];
    uint8_t count;
}Menu;

typedef struct{
    uint8_t name[NAME_SIZE];
    uint8_t status[NAME_SIZE];
}History;

uint8_t *fruits[] = {"Lemon", "Apple", "Peach", "Melon", "Orange"};
Menu *mptr = NULL;
History history[ORDER_SIZE];
uint8_t history_count = 0;

void init(Menu *);
void print_menu(Menu *);
void order_history();
void check(Menu *, uint8_t *, int32_t);
void handler();

int main(int argc, char *argv[], char *envp[]){
    Menu menu[MENU_SIZE] = {0, };
    uint8_t input[NAME_SIZE], child_data[NAME_SIZE];
    ssize_t size;
    int8_t num = 3;
    pid_t pid, waitpid;
    int32_t status, order_pipe[2];

    init(menu);

    while(num){
        print_menu(menu);
        printf("Enter a menu: ");
        memset(input, '\0', sizeof(input));
        size = read(0, input, sizeof(input));
        input[size-1] = '\0';

        pipe(order_pipe);
        pid = fork();
        if(pid > 0){ // Parent
            close(order_pipe[1]);
            waitpid = wait(&status);
            if(WIFEXITED(status)){
                memset(child_data, '\0', sizeof(child_data));
                read(order_pipe[0], child_data, sizeof(child_data));
                if(WEXITSTATUS(status) == 7){
                    for(uint8_t i = 0; i < MENU_SIZE; i++){
                        if(strcmp(menu[i].name, child_data)) continue;
                        menu[i].count--;
                        memset(history[history_count].name, '\0', sizeof(history[history_count].name));
                        memset(history[history_count].status, '\0', sizeof(history[history_count].status));
                        strcpy(history[history_count].name, menu[i].name);
                        strcpy(history[history_count].status, "Successful!");
                        history_count++;
                        break;
                    }
                    printf("Successful!\n\n");
                    num--;
                }else if(WEXITSTATUS(status) == 8){
                    _Bool flag = 0;
                    for(uint8_t i = 0; i < MENU_SIZE; i++){
                        if(strcmp(menu[i].name, child_data)) continue;
                        memset(history[history_count].name, '\0', sizeof(history[history_count].name));
                        memset(history[history_count].status, '\0', sizeof(history[history_count].status));
                        strcpy(history[history_count].name, menu[i].name);
                        strcpy(history[history_count].status, "Failed...");
                        history_count++;
                        // flag = 1;
                        break;
                    }
                    printf("Failed...\n\n");
                    num--;
                    // if(flag == 0){
                    //     memset(history[history_count].name, '\0', sizeof(history[history_count].name));
                    //     memset(history[history_count].status, '\0', sizeof(history[history_count].status));
                    //     strcpy(history[history_count].name, child_data);
                    //     strcpy(history[history_count].status, "Failed...");
                    //     history_count++;
                    // }
                }
                // else if(WEXITSTATUS(status) == 9){
                // }
            }
        }else if(pid == 0){ // Child
            close(order_pipe[0]);
            check(menu, input, order_pipe[1]);
        }else{
            exit(-1);
        }
    }
    order_history();
}

void init(Menu *m){
    mptr = m;
    srand(time(NULL));
    signal(SIGINT, handler);

    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    remove("Order_History.txt");

    for(uint8_t i = 0; i < MENU_SIZE; i++){
        memset(m[i].name, '\0', sizeof(m[i].name));
        strcpy(m[i].name, fruits[i]);
        m[i].count = rand() % 3;
    }
}

void handler(){
    order_history();
    exit(0);
}

void print_menu(Menu *m){
    puts("--- Menu List --- ");
    for(uint8_t i = 0; i < MENU_SIZE; i++){
        printf("%s : %hhu\n", m[i].name, m[i].count);
    }
    puts("");
}

void order_history(){
    FILE *fp;
    uint8_t tmp[0x20];
    memset(tmp, '\0', sizeof(tmp));
    printf("\n\n\n--- Your Order History --- \n");
    // if(history_count == 0){
    //     puts("None");
    //     return;
    // }
    fp = fopen("Order_History.txt", "r");
    if(fp == NULL){
        puts("None");
        return;
    }
    for(uint8_t i = 0; i < history_count; i++){
        while(fgets(tmp, sizeof(tmp), fp) != NULL){
            printf("%s", tmp);
        }
    }
    fclose(fp);
}

void check(Menu *m, uint8_t *str, int32_t pipenum){
    FILE *fp;
    if(history_count == 0) fp = fopen("Order_History.txt", "w");
    else fp = fopen("Order_History.txt", "a+");
    for(uint8_t i = 0; i < MENU_SIZE; i++){
        if(strcmp(m[i].name, str)) continue;
        if(m[i].count >= 1){
            fprintf(fp, "Order 1 %s, %s\n", str, "Successful!");
            fclose(fp);
            write(pipenum, str, strlen(str));
            exit(7);
        }else{
            fprintf(fp, "Order 1 %s, %s\n", str, "Failed...");
            fclose(fp);
            write(pipenum, str, strlen(str));
            exit(8);
        }
    }
    // fprintf(fp, "Order 1 %s, %s\n", str, "Failed...");
    // fclose(fp);
    // write(pipenum, str, strlen(str));
    exit(9);
}