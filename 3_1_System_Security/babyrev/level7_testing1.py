from pwn import *

filename = 'babyrev_level7_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

l = [0xca,0x11,0xfb,0x99,0x5d,0xaa,0xc9,0x0c]
for i in range(len(l)):
    if i % 3 == 0:
        l[i] ^= 0x1a
    elif i % 3 == 1:
        l[i] ^= 0x99
    else:
        l[i] ^= 0x2E

for i in range(len(l)):
    l[i] ^= 0x76

for i in range(len(l)):
    if i % 2 == 0:
        l[i] ^= 0xd7
    else:
        l[i] ^= 0x99

answer = ''.join(list(map(chr, l)))
answer = 'a'*9 + answer
print(answer)

code = '''
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    size_t fd = open("/tmp/zz", 0);
    dup2(fd, 681);
    execve("/babyrev_level7_testing1", NULL, NULL);
    return 0;
}
'''
shell.sendline(f"echo '{answer}' > /tmp/zz")
shell.sendline(f"cd /tmp && echo '{code}' > a.c && gcc -o a a.c && chmod +x a && ./a")

shell.interactive()

# p.interactive()
