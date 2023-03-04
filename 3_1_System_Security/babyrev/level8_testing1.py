from pwn import *

filename = 'babyrev_level8_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

shell.sendline(f'ln -s /{filename} /tmp/zzlol')

p = s.process('zzlol', cwd='/tmp')

enc = '_XYYYFMKDEFS'
k = [x^0x3c for x in list(map(ord, enc))]
k[5], k[11] = k[11], k[5]
print(k)
flag = 'A' * 12 + ''.join(map(chr,k))
# sort -> swap(5, 11) -> xor with 0x33

code = f'''
from socket import *

sock = socket(AF_UNIX, SOCK_STREAM)
sock.connect("/tmp/opiou")
sock.sendall(b"{flag}")
sock.close()
'''

shell.sendline(f"echo '{code}' > /tmp/client.py && python /tmp/client.py".encode())

p.interactive()
