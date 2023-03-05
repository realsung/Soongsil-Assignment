from pwn import *

filename = 'babyrev_level10_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

e = [0xC8, 0xF1, 0x54, 0xFE, 0xCD, 0x1D, 0xB9, 0x85, 0x5D, 0xF8]

for i in range(len(e)):
    if i % 2 == 0:
        e[i] ^= 0x9D
    else:
        e[i] ^= 0xce

e[0], e[1] = e[1], e[0]

e.reverse()

for i in range(len(e)):
    if i % 3 == 0:
        e[i] ^= 0x53
    elif i % 3 == 1:
        e[i] ^= 0xba
    else:
        e[i] ^= 0x3a

flag = ''.join(map(chr, e))
flag = '/tmp/zzloll' + flag
# .//zzlollezqwijcsol!

shell.sendline(f'ln -s /{filename} {flag}')

p = s.process('./' + flag[5:], cwd='/tmp')

p.interactive()
