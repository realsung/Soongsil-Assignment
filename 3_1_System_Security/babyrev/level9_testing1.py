from pwn import *

filename = 'babyrev_level9_testing1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

shell.sendline(f'ln -s /{filename} /tmp/zzlol')

p = s.process('zzlol', cwd='/tmp')

enc = list(map(ord, 'egjlmotuwx'))
enc[0], enc[3] = enc[3], enc[0]
enc.reverse()
enc[1], enc[2] = enc[2], enc[1]
flag = 'a'*0xc + ''.join(map(chr, enc))
print(flag)

code = f'''
from socket import *

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(("127.0.0.1", 45827))
sock.sendall(b"{flag}")
sock.close()
'''

shell.sendline(f"echo '{code}' > /tmp/client.py && python /tmp/client.py")

# shell.interactive()

p.interactive()
