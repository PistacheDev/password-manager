import encryptor # encryptor.py
import base64
import os
from Crypto.Cipher import AES
from Crypto.Protocol.KDF import PBKDF2

def createPassword():
    masterPassword = input('Master password: ')
    success = encryptor.verifyMaster(masterPassword)

    if success == False:
        print('Incorrect master password!')
    else:
        salt = os.urandom(16)
        key = encryptor.generateValidKey(masterPassword, salt)
        name = input('New password\'s name: ')

        if os.path.isfile(f'./pwd/{name}.md'):
            allowed = input(f'"{name}" already exists, do you want to overwrite the data? (y/n) ')
            if allowed.lower() == 'n':
                return None

        password = input('Password: ')
        data = password.encode()
        encoded = encryptor.encryptData(key, data)

        with open(f'./pwd/{name}.md', 'w') as pwdFile:
            pwdFile.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encoded}')

        print('Password created successfuly!')
    input('\nPress [Enter] to continue..')

def removePassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword)

        if success == False:
            print('Incorrect master password!')
        else:
            for file in files:
                passwords.append(file.split('.md')[0])

            print(f'Available passwords: {', '.join(passwords)}')
            name = input('Password\'s name: ')

            if os.path.isfile(f'./pwd/{name}.md'):
                os.remove(f'./pwd/{name}.md')
                print('Password removed successfuly!')
            else:
                print('This password doesn\'t exist!')

    input('\nPress [Enter] to continue..')

def showPassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword)

        if success == False:
            print('Incorrect master password!')
        else:
            salt = os.urandom(16)
            key = encryptor.generateValidKey(masterPassword, salt)

            for file in files:
                passwords.append(file.split('.md')[0])

            print(f'Available passwords: {', '.join(passwords)}')
            name = input('Password\'s name: ')

            if os.path.isfile(f'./pwd/{name}.md'):
                with open(f'./pwd/{name}.md', 'r') as pwdFile:
                    content = pwdFile.read()
                    salt, encoded = content.split(':')
                    salt = base64.urlsafe_b64decode(salt)
                    key = encryptor.generateValidKey(masterPassword, salt)
                    password = encryptor.decryptData(key, encoded)
                    print(f'{name}\'s password: {password}')
            else:
                print(f'Password "{name}" doesn\'t exist!')
    input('\nPress [Enter] to continue..')

def changeMaster():
    current = input('Current master password: ')
    success = encryptor.verifyMaster(current)

    if success == False:
        print('Incorrect master password!\n')
    else:
        new = input('New master password: ')
        salt = os.urandom(16)
        key = encryptor.generateValidKey(new, salt)
        encoded = encryptor.encryptData(key, new.encode())

        with open(f'master.md', 'w') as master:
            master.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encoded}')
            print('Master password successfuly updated!\n')
    input('Press [Enter] to continue..')