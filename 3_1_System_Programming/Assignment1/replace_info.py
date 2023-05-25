import os

filename = ['file1.o', 'file2.o', 'file3.o']
myPath = os.getcwd()

for name in filename:
    getName = myPath + '/' + name
    if os.path.exists(getName) and os.path.isfile(getName):
        print(f'[!] Found {getName} File.')
    else:
        print(f'[*] Not Found {getName} File.')

with open('file2.o','rb') as f1:
    data = f1.read().replace(b'20081234', b'20211687')
    with open('file2.o','wb') as f2:
        f2.write(data)

with open('file3.o','rb') as f1:
    data = f1.read().replace(b'Young-Ho Gong', b'Sung-Jun Park')
    with open('file3.o','wb') as f2:
        f2.write(data)
