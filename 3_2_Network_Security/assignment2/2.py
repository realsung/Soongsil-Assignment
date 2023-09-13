# import struct
# with open('enc1.txt', 'rb') as f:
#     size = struct.unpack('<L', f.read(4))[0]
#     enc = f.read()

#     key = 'ABCDEF0123456789'
#     iv = 'Netsec@Soongsil.'
    

#     print(enc)

from Crypto.Cipher import AES
from Crypto.Hash import SHA256
import os, random, struct

def decrypt_file(key, filename):
	
	chunk_size = 1024
	
	output_filename = os.path.splitext(filename)[0]+'.decrypted'
	
	#open the encrypted file and the initialization vector. 
	#The IV is required for creating the cipher.
	with open(filename, 'rb') as infile:
		iv = b'Netsec@Soongsil.'
		origsize = struct.unpack('<L', infile.read(4))[0]
	
		#create the cipher using the key and the IV.
		decryptor = AES.new(key, AES.MODE_CBC, iv)
		
		#We also write the decrypted data to a verification file, 
		#so we can check the results of the encryption 
		#and decryption by comparing with the original file.
		with open(output_filename, 'wb') as outfile:
			while True:

				chunk = infile.read(chunk_size)
				if len(chunk) == 0:
					break
				outfile.write(decryptor.decrypt(chunk))
			outfile.truncate(origsize)

key = b'ABCDEF0123456789'

decrypt_file(key, 'enc1.txt')
