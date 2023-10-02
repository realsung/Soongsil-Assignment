'''
• 키쌍생성
• 공개키를 public.der로 저장 (der 인코딩으로 저장)
• 1.txt 를 읽어서 서명 후 서명 값은 Base64 encoding하여 sig.txt에 저장
☞ 문서와 sign 을 저장하기 위해 표준화된 asn.1 포맷 (PKCS#7) 이 따로 있음
'''
from Crypto.PublicKey import RSA
from Crypto.Signature import PKCS1_PSS
from Crypto.Hash import SHA
import base64

keyPair = RSA.generate(2048)
pubkey = keyPair.publickey()
pubkeyDER = pubkey.export_key(format='DER')

with open('public.der', 'wb') as f:
    f.write(pubkeyDER)

with open('1.txt', 'r') as f:
    message = f.read().encode()

signer = PKCS1_PSS.new(keyPair)
h = SHA.new()
h.update(message)
signature = signer.sign(h)
print(signature)

with open('sig.txt', 'w') as f:
    f.write(base64.b64encode(signature).decode())

