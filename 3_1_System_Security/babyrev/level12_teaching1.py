from pwn import *
import binascii

filename = '/babyrev_level12_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
p = s.process([filename, 'aaaaaaaaaaaaaaaa'], cwd='/tmp')

p.sendlineafter(b'Offset (hex) to change:', b'D31')
p.sendlineafter(b'New value (hex):', b'90')
p.interactive()

# e = [0xAE, 0x34, 0xC3, 0x1B, 0x8, 0x89, 0x0E, 0x5, 0x0E, 0xBA, 0x88, 0x16, 0xB1, 0x6C, 0x29, 0x17]
# a = bytes(e).hex()
# print(a)