#include "types.h"
#include "user.h"
int main(int argc, char *argv[]) {
    const char *args[] = {"echo", "NEWPROC_CALL", 0};
    int ret;
    printf(1, "Test forknexec syscall\n");
    ret = forknexec(args[0], args);
    printf(1, "returned: %d\n", ret);
    exit();
}