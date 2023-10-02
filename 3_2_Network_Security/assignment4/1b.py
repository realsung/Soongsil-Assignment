from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import binascii

with open('Alice_public.pem', 'r') as f:
    pubkey = RSA.importKey(f.read())

with open('1.txt', 'r') as f:
    message = f.read().encode()

encryptor = PKCS1_OAEP.new(pubkey)
encrypted = encryptor.encrypt(message)
# print(encrypted)
# print(b"Encrypted:", binascii.hexlify(encrypted))

with open('Enc.txt', 'wb') as f:
    f.write(encrypted)

