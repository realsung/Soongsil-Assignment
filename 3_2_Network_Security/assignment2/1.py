from Crypto.Cipher import AES
import random

if __name__ == '__main__':
    while True:
        p = input("Enter plaintext: ").encode()
        key = b'secret-key-01234'
        iv = b'IV-0123456789ABC'
        aes = AES.new(key, AES.MODE_CFB, iv)
        ciphertext = aes.encrypt(p)
        print(f'[*] encrypted: {ciphertext}')

        aes2 = AES.new(key, AES.MODE_CFB, iv)
        plaintext = aes2.decrypt(ciphertext)
        print(f'[*] decrypted: {plaintext}')
