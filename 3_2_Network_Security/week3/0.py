from Crypto.Hash import SHA256
from bitstring import BitArray


for i in range (1000000) :
	b= i.to_bytes(5, 'big')
	h=SHA256.new(b) 
	hash=h.digest()

	c=BitArray( hash)
	print (hash[0:1], c.bin[:8])
	
	if hash[0:1] == bytes(1) :	
		c=BitArray(hash)
		print ("found", i, c.bin[:8]) 
		break

