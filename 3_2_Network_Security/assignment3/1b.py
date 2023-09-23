from Crypto.Hash import HMAC

# key = b'THISISKEY'
key = input('input key : ').encode()

with open('H.txt', 'rb') as f:
	message = f.read()
	g = message[:-16]
	m = message[-16:]
	h = HMAC.new(key)
	h.update(g)
	mac = h.digest()
	print(f'mac : {mac}')
	if m == mac:
		print(b'OK')
	else:
		print(b'NOK')