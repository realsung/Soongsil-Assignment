from Crypto.Hash import HMAC

# key = b'THISISKEY'
key = input('input key : ').encode()

with open('1.txt', 'rb') as f:
	message = f.read()
	h = HMAC.new(key)
	with open('H.txt', 'wb') as f2:
		h.update(message)
		mac = h.digest()
		print(f'mac : {mac}')
		f2.write(message)
		f2.write(mac)

	
# from Crypto.Cipher import AES
# from Crypto.Hash import SHA256, HMAC
# import os, random, struct

# def encrypt_file(key, filename):
# 	chunk_size = 1024
# 	# output_filename = filename + '.encrypted'
# 	output_filename = 'H.txt'
	
# 	h = HMAC.new(key)
	
# 	filesize = os.path.getsize(filename)
	
# 	with open(filename, 'rb') as inputfile:
# 		with open(output_filename, 'wb') as outputfile:
# 			# outputfile.write(struct.pack('<Q', filesize))
# 			while True:
# 				chunk = inputfile.read(chunk_size)
# 				if len(chunk) == 0:
# 					break
# 				elif len(chunk) % 16 != 0:
# 					chunk += b' ' * (16 - len(chunk) % 16)

# 				h.update(chunk)
# 				mac = h.digest()
# 				outputfile.write(mac)

# key = b'THISISKEY'

# encrypt_file(key, '1.txt')