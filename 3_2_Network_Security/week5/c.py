import socket
import json
import base64

from Crypto import Random
from Crypto.Hash import SHA


comSocket = socket.socket()

svrIP = "127.0.0.1"
comSocket.connect((svrIP,2500))
print('\tConnected to '+svrIP)

uid = input(("id: "))

msg1=  json.dumps ( {'uid': uid })
comSocket.send(msg1.encode()) 
print ("\tSent : ", msg1)

msg2= comSocket.recv(1024).decode()
nonceStr=json.loads( msg2)['nonce'].encode()
nonce=base64.b64decode( nonceStr )
print ("\tReceived : ", msg2)

pw = input("password: ").encode()
h=SHA.new( pw+nonce).digest()
hStr=base64.b64encode(h).decode()
msg3=  json.dumps ( {'h': hStr })
comSocket.send(msg3.encode()) 
print ("\tSent : ", msg3)

