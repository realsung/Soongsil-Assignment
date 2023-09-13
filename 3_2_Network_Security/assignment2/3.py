from Crypto.Cipher import AES
from Crypto.Hash import SHA256
import os, random, struct
from Crypto.Util import Counter

ctr=Counter.new(128) # bits, block size

def decrypt_file(key, filename):
	
	chunk_size = 1024
	
	output_filename = os.path.splitext(filename)[0]+'.decrypted'
	
	#open the encrypted file and the initialization vector. 
	#The IV is required for creating the cipher.
	with open(filename, 'rb') as infile:
		# iv = infile.read(16)
		
		origsize = struct.unpack('<L', infile.read(4))[0]

		#create the cipher using the key and the IV.
		decryptor = AES.new(key, AES.MODE_CTR, counter=ctr)
		
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
	
decrypt_file(key, 'enc2.txt')
