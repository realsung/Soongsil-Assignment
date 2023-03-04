from pwn import *

filename = 'babyrev_level8_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
shell = s.shell("/bin/sh")

shell.sendline(f'ln -s /{filename} /tmp/zzlol')

p = s.process('zzlol', cwd='/tmp')

flag = 'a'*9 + 'dgggjtvvwxyz'

code = f'''
from socket import *

sock = socket(AF_UNIX, SOCK_STREAM)
sock.connect("/tmp/pfrvi")
sock.sendall(b"{flag}")
sock.close()
'''

shell.sendline(f"echo '{code}' > /tmp/client.py && python /tmp/client.py")

p.interactive()
