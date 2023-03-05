from pwn import *
import binascii

filename = '/babyrev_level11_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
p = s.process([filename, 'aaaaaaaaaaaaaaaa'], cwd='/tmp')

p.sendlineafter(b'Offset (hex) to change:', b'801')
p.sendlineafter(b'New value (hex):', b'90')
p.sendlineafter(b'Offset (hex) to change:', b'801')
p.sendlineafter(b'New value (hex):', b'90')
p.sendlineafter(b'Offset (hex) to change:', b'801')
p.sendlineafter(b'New value (hex):', b'90')
p.sendlineafter(b'Offset (hex) to change:', b'802')
p.sendlineafter(b'New value (hex):', b'90')
p.sendlineafter(b'Offset (hex) to change:', b'802')
p.sendlineafter(b'New value (hex):', b'90')

p.interactive()