import encryptor # encryptor.py
import base64
import os
import shutil

def createPassword():
    masterPassword = input('Master password: ')
    success = encryptor.verifyMaster(masterPassword)

    if not success:
        print('Incorrect master password!')
    else:
        salt = os.urandom(16) # Generate a random 16 bytes salt.
        key = encryptor.generateValidKey(masterPassword, salt) # Generate a valid key for the encryption.
        name = input('Password name (example: Gmail): ')

        if os.path.isfile(f'./pwd/{name}.md'):
            allowed = input(f'"{name}" already exists, do you want to overwrite the actual data? (y/n) ')
            if allowed.lower() == 'n':
                return None

        password = input('Password: ')
        encrypted = encryptor.encryptData(key, password.encode())

        with open(f'./pwd/{name}.md', 'w') as pwdFile:
            pwdFile.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encrypted}') # Encode the salt with base64 and add it to the encrypted password.
            print('Password created successfully!')

        # Remove every sensitive data from the memory.
        encryptor.deleteSensitiveData(salt)
        encryptor.deleteSensitiveData(key)
        encryptor.deleteSensitiveData(password)

    encryptor.deleteSensitiveData(masterPassword) # Remove the master password from the memory.
    input('\nPress [Enter] to continue..')

def removePassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword)

        if not success:
            print('Incorrect master password!')
        else:
            for file in files:
                passwords.append(file.split('.md')[0])

            print(f'Available passwords: {', '.join(passwords)}') # Create a list with every the available passwords.
            name = input('Password name (enter [*] to remove everything): ')

            if name == '*':
                shutil.rmtree('./pwd')
                os.mkdir('pwd')
                print(f'{len(passwords)} passwords removed successfully!')
            elif os.path.isfile(f'./pwd/{name}.md'):
                os.remove(f'./pwd/{name}.md')
                print('Password removed successfully!')
            else:
                print('This password doesn\'t exist!')

    encryptor.deleteSensitiveData(masterPassword) # Remove the master password from the memory.
    input('\nPress [Enter] to continue..')

def showPassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword)

        if not success:
            print('Incorrect master password!')
        else:
            for file in files:
                passwords.append(file.split('.md')[0])

            print(f'{len(passwords)} available passwords: {', '.join(passwords)}') # Create a list with every available passwords.
            name = input('Password name (enter [*] to show every passwords): ')

            if name == '*':
                for i in range(len(passwords)):
                    if os.path.isfile(f'./pwd/{passwords[i]}.md'):
                        displayPassword(masterPassword, passwords[i])
            elif os.path.isfile(f'./pwd/{name}.md'):
                displayPassword(masterPassword, name)
            else:
                print(f'Password "{name}" doesn\'t exist!')

            encryptor.deleteSensitiveData(masterPassword) # Remove the master password from the memory.
    input('\nPress [Enter] to continue..')

def displayPassword(masterPassword, name):
    with open(f'./pwd/{name}.md', 'r') as pwdFile:
        salt, encoded = pwdFile.read().split(':')
        salt = base64.urlsafe_b64decode(salt) # Decode the salt with base64.
        key = encryptor.generateValidKey(masterPassword, salt) # Generate a valid key for the decryption.
        password = encryptor.decryptData(key, encoded) # Decrypt the password with the generated key.
        if password:
            print(f'{name}: {password}')

    # Remove every sensitive data from the memory.
    encryptor.deleteSensitiveData(salt)
    encryptor.deleteSensitiveData(key)
    encryptor.deleteSensitiveData(password)

def changeMaster():
    current = input('Current master password: ')
    success = encryptor.verifyMaster(current)

    if not success:
        print('Incorrect master password!\n')
    else:
        new = input('New master password: ')
        salt = os.urandom(16) # Generate a random salt.
        key = encryptor.generateValidKey(new, salt) # Generate a valid key for the encryption.
        encrypted = encryptor.encryptData(key, new.encode())

        with open(f'master.md', 'w') as master:
            master.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encrypted}') # Encode the salt with base64 and add it to the encrypted password.
            print('Master password successfuly updated!')

        # Remove every sensitive data from the memory.
        encryptor.deleteSensitiveData(new)
        encryptor.deleteSensitiveData(salt)
        encryptor.deleteSensitiveData(key)
    input('\nPress [Enter] to continue..')