from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

passphrase = input("Enter passphrase: ")
with open('Alice_private.pem', 'r') as f:
    keyPair = RSA.importKey(f.read(), passphrase=passphrase)

with open("Enc.txt", "rb") as f:
    encrypted = f.read()

decryptor = PKCS1_OAEP.new(keyPair)
decrypted = decryptor.decrypt(encrypted)
print('Decrypted:', decrypted.decode())