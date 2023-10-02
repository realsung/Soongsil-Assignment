'''
Public.der와 sig.txt, 1.txt을 읽어서
• 1.txt에 대한 서명을 검증하는 코드를 작성 , 맞으면 "verified" 틀리면 "not
verified"를 출력
- 1.txt의 한글자만 바꿔도 not verified가 되어야 함
'''
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_PSS
from Crypto.Hash import SHA
import base64

with open('public.der', 'rb') as f:
    pubkey = RSA.importKey(f.read())

with open('1.txt', 'r') as f:
    message = f.read().encode()

with open('sig.txt', 'r') as f:
    signature = base64.b64decode(f.read())

verifier = PKCS1_PSS.new(pubkey)
h = SHA.new()
h.update(message)
if verifier.verify(h, signature):
    print("verified")
else:
    print("not verified")