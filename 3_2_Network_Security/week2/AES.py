
# AES pycrypto package
from Crypto.Cipher import AES

# key has to be 16, 24 or 32 bytes long
encrypt_AES = AES.new(b'secret-key-01234', AES.MODE_CBC, b'IV-0123456789ABC')

# Fill with spaces the user until 32 characters
message = b"This is the secret message      " 
print ("message length: ", len(message) )

ciphertext = encrypt_AES.encrypt(message)
print("Cipher text: " , ciphertext)

# key must be identical
decrypt_AES = AES.new(b'secret-key-01234', AES.MODE_CBC, b'IV-0123456789ABC')
message_decrypted =  decrypt_AES.decrypt(ciphertext)

print("Decrypted text: ",  message_decrypted.strip())
