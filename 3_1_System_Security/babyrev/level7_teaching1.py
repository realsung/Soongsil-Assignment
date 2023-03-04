from pwn import *

filename = 'babyrev_level7_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

code = '''
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    size_t fd = open("/tmp/zz", 0);
    dup2(fd, 900);
    execve("/babyrev_level7_teaching1", NULL, NULL);
    return 0;
}
'''
shell.sendline("echo aaaaaavmhgyatintntyeay > /tmp/zz")
shell.sendline(f"cd /tmp && echo '{code}' > a.c && gcc -o a a.c && chmod +x a && ./a")

shell.interactive()

# p.interactive()
