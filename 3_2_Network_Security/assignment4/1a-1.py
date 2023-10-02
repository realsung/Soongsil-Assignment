from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import binascii

keyPair = RSA.generate(2048)
# print(keyPair.n)
# print(keyPair.e)
# print(hex(keyPair.n))
# print(len(hex(keyPair.n)))

pubkey = keyPair.publickey()
# encryptor = PKCS1_OAEP.new(pubkey)
# encrypted = encryptor.encrypt(b'Hello World')
# print("Encrypted:", binascii.hexlify(encrypted))

# decryptor = PKCS1_OAEP.new(keyPair)
# decrypted=decryptor.decrypt(encrypted)
# print('Decrypted:', decrypted)

priKeyPEM= keyPair.export_key (passphrase="1234")
# print (priKeyPEM)
keyPair= RSA.importKey(priKeyPEM, passphrase="1234" )

pubKeyPEM=pubkey.export_key()
pubKey= RSA.importKey(pubKeyPEM)

with open('Alice_private.pem', 'w') as f:
    f.write(priKeyPEM.decode())

with open('Alice_public.pem', 'w') as f:
    f.write(pubKeyPEM.decode())