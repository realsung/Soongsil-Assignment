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

// #include "types.h"
// #include "user.h"

// #define PASSED 0
// #define FAILED 1

// int test(const char *args[], int expected)
// {
//     int ret = forknexec(args[0], args);
//     if (ret == expected)
//     {
//         return PASSED;
//     }
//     return FAILED;
// }

// void testAndPrint(const char *name, const char *args[], int expected)
// {
//     int result = test(args, expected);
//     if (result == PASSED)
//     {
//         printf(1, "%s: PASSED\n", name);
//         return;
//     }
//     printf(1, "%s: FAILED\n", name);
// }

// int main(int argc, char *argv[])
// {
//     const char *argsNormal[] = {"echo", "NEWPROC_CALL", 0};
//     const char *argsNull[] = {0};
//     testAndPrint("normal", argsNormal, getpid() + 1);
//     testAndPrint("null", argsNull, -1);
//     exit();
// }