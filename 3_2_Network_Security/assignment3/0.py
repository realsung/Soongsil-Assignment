from Crypto.Hash import SHA256, SHA384
from bitstring import BitArray


# for i in range (20000000, 40000000) :
# 	b= i.to_bytes(5, 'big')
# 	h=SHA384.new(b) 
# 	hash=h.digest()

# 	c=BitArray( hash)
# 	print (hash[0:3], c.bin[:24])
	
# 	if hash[0:3] == bytes(3) :	
# 		c=BitArray(hash)
# 		print ("found", i, c.bin[:24]) 
# 		break

for i in range (20000000, 40000000) :
	b= i.to_bytes(5, 'big')
	h=SHA384.new(b) 
	hash=h.digest()

	c=BitArray( hash)
	print (hash[0:3], c.bin[:24])
	
	if hash[0:3] == bytes(3) :	
		c=BitArray(hash)
		print ("found", i, c.bin[:24]) 
		break


