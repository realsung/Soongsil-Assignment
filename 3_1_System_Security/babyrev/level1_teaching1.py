from pwn import *

filename = './babyrev_level1_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")
p = s.process([filename, 'ivz'])

p.interactive()