from Crypto.PublicKey import RSA

key=RSA.generate(2048)

from Crypto.Signature import PKCS1_PSS
from Crypto.Hash import SHA
msg = b"To be signed"
h= SHA.new( )
h.update ( msg )
signer=PKCS1_PSS.new ( key )
sig=signer.sign ( h ) # hash값을 넣어줘야 함
print (sig)

h = SHA.new( )
h.update ( msg )
pubKey=key.publickey( ) # 공개키만 있으면 검증 가능
verifier=PKCS1_PSS.new ( pubKey )
print(verifier.verify ( h, sig ))