from Crypto.Hash import HMAC

#sender

h=HMAC.new( b'password') 
h.update (b'message')
mac= h.digest()

#receiver

h=HMAC.new( b'password')
h.update (b'message')
mac2= h.digest()


if mac == mac2 : 
	print ("ok")

