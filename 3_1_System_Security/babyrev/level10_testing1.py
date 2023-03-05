from pwn import *

filename = 'babyrev_level10_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

e = list(map(ord,'kCfAbFcEz^{^vSuSrVpU'))

for i in range(len(e)):
    if i % 2 == 0:
        e[i] ^= 0x11
    else:
        e[i] ^= 0x34

e.reverse()

e[4], e[5] = e[5], e[4]

flag = ''.join(map(chr, e))
flag = '/tmp/zxczxczxczxczx' + flag
print(flag)

shell.sendline(f'ln -s /{filename} {flag}')

exe = './' + flag[5:]
print(exe)

p = s.process(exe, cwd='/tmp')

p.interactive()
