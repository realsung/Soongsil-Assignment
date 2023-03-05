from pwn import *

filename = './babyrev_level6_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")

command = 'ln -s /{} /tmp/zzlol'.format(filename)
s[command]

p = s.process('./zzlol', cwd='/tmp')

command = 'echo "{}" > /tmp/ozvov'.format('aaaaaa' + 'iqtgjvamgoxp')
s[command]

p.interactive()

'''
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
        size_t fd = open("/tmp/llgwv", O_RDWR);
        char *buf = "aaaaaavmhtyaaintntyegy";
        write(fd, buf, strlen(buf));
        return 0;
}
'''