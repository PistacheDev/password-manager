import os
import encryptor # encryptor.py
from Crypto.Cipher import AES
import base64
import pwdManager # pwdManager.py
import pwdGenerator # pwdGenerator.py
import sys
import os
import platform

# First launch setup.
with open('master.md', 'r') as master:
    if master.read() == 'None':
        setup = input('Create your master password: ')
        salt = os.urandom(16)
        key = encryptor.generateValidKey(setup, salt)
        encoded = encryptor.encryptData(key, setup.encode())

        with open(f'master.md', 'w') as master:
            master.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encoded}')
            print('Master password successfuly created!\nDon\'t forget it, because you can\'t reset it and can\'t get your passwords back without it.')
            input('Press [Enter] to continue..')
            os.system('cls' if platform.system() == 'Windows' else 'clear')

if not os.path.exists('./pwd'): # Create the passwords's folder storage.
    os.mkdir('pwd')

while True:
    print('What do you want to do?')
    print('1) Add a new password.')
    print('2) Remove a password.')
    print('3) Show a password.')
    print('4) Generate a new password.')
    print('5) Change the master password.')
    print('6) Close the program.', end = '\n\n')
    option = input('Option\'s number: ')

    while True:
        if option == '1':
            pwdManager.createPassword()
            break
        elif option == '2':
            pwdManager.removePassword()
            break
        elif option == '3':
            pwdManager.showPassword()
            break
        elif option == '4':
            pwdGenerator.generatePassword()
            break
        elif option == '5':
            pwdManager.changeMaster()
            break
        elif option == '6':
            sys.exit()
        else:
            print('Please, try again.', end = '\n\n')
            option = input('Option\'s number: ')

    os.system('cls' if platform.system() == 'Windows' else 'clear')