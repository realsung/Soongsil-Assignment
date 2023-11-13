#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
    printf(1, "[+] PROCESS LOOP!\n");
    int pid = getpid();
    int priority = atoi(argv[1]);
    set_proc_priority(pid, priority);
    printf(1, "[-] PROCESS pid: %d, priority: %d\n", pid, priority);
    while(1);
}