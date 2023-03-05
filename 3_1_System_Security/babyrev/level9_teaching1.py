from pwn import *

filename = 'babyrev_level9_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

shell.sendline(f'ln -s /{filename} /tmp/zzlol')

p = s.process('zzlol', cwd='/tmp')

enc = [0x33, 0x0D, 0xC4, 0xB, 0x8, 0x3D, 0xCC, 0x13, 0x3C, 0x1E]
enc[4], enc[5] = enc[5], enc[4]
for i in range(len(enc)):
    if i % 4 == 0:
        enc[i] ^= 0x56
    elif i % 4 == 1:
        enc[i] ^= 0x67
    elif i % 4 == 2:
        enc[i] ^= 0xbd
    elif i % 4 == 3:
        enc[i] ^= 0x60

enc[2], enc[8] = enc[8], enc[2]
flag = 'a'*8 + ''.join(map(chr, enc))
print(flag)
# flag = 'a'*9 + 'dgggjtvvwxyz'

code = f'''
from socket import *

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(("127.0.0.1", 42334))
sock.sendall(b"{flag}")
sock.close()
'''

shell.sendline(f"echo '{code}' > /tmp/client.py && python /tmp/client.py")

# shell.interactive()

p.interactive()
