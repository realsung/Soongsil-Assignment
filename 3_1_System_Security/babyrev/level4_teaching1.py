from pwn import *

filename = 'babyrev_level4_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")

command = 'echo "{}" > /tmp/vxhsq'.format('aaaacfknrs')
s[command]

command = 'ln -s /{} /tmp/zzlol'.format(filename)
s[command]

p = s.process('./zzlol', cwd='/tmp')

p.interactive()