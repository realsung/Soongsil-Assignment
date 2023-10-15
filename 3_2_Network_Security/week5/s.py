import socket
import json
import base64

from Crypto import Random
from Crypto.Hash import SHA

idpw = { 'Alice':'1234', 'Bob':'abcd' }

com_socket = socket.socket()
com_socket.bind(('127.0.0.1',2500))
com_socket.listen(10)

print('Waiting connection from client... ')

connection, address =com_socket.accept()
print('Connected from client... ')

msg1 =connection.recv(1024).decode()
uid=json.loads( msg1)['uid']
print ("\nReceived : ", msg1)

nonce= Random.get_random_bytes (8)
nonceStr=base64.b64encode(nonce).decode()
msg2=  json.dumps ( {'nonce': nonceStr })

connection.send(msg2.encode()) 
print ("\nSent : ", msg2)

msg3 =connection.recv(1024).decode()
hStr= json.loads( msg3) ['h'].encode()
h=base64.b64decode (hStr)
print ("\nReceived : ", msg3)

pw = idpw[uid].encode()
h2=SHA.new( pw+nonce).digest()

if  h== h2 :
    print ("\nVerified: ", uid)

