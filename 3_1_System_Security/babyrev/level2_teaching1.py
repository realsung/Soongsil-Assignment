from pwn import *

filename = './babyrev_level2_teaching1'

context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../csec")

argv = [filename]
for i in range(310):
    argv.append('a')

p = s.process(argv)

p.interactive()