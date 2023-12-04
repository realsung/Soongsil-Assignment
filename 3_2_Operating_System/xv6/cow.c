#include "types.h"
#include "stat.h"
#include "user.h"

int global = 0;

void test1(){
    printf(1, "Before fork() getNumFreePages() = %d\n", getNumFreePages());
    int pid = fork();
    if(pid == 0){ // Child
        printf(1, "[-] Child: global = %d, getNumFreePage() = %d\n", global, getNumFreePages());
        global = 1;
        printf(1, "[+] Child: global = %d, getNumFreePage() = %d\n", global, getNumFreePages());
    }else{ // Parent
        printf(1, "[-] Parent: global = %d, getNumFreePage() = %d\n", global, getNumFreePages());
        wait();
        printf(1, "[+] Parent: global = %d, getNumFreePage() = %d\n", global, getNumFreePages());
    }
    printf(1, "After fork() getNumFreePages() = %d\n", getNumFreePages());
}

void test2(){
    printf(1, "Before sbrk() getNumFreePages() = %d\n", getNumFreePages());
    sbrk(4096);
    printf(1, "After sbrk() getNumFreePages() = %d\n", getNumFreePages());
}

int main(void)
{
    test1();
    // test2();
    exit();
}