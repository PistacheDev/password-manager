import encryptor # encryptor.py
import base64
import os

def createPassword():
    masterPassword = input('Master password: ')
    success = encryptor.verifyMaster(masterPassword) # Check if the provided master password is correct.

    if not success:
        print('Incorrect master password!')
    else:
        salt = os.urandom(16) # Generate a random salt.
        key = encryptor.generateValidKey(masterPassword, salt) # Generate a valid key for the encryption.
        name = input('New password\'s name: ')

        if os.path.isfile(f'./pwd/{name}.md'):
            allowed = input(f'"{name}" already exists, do you want to overwrite the data? (y/n) ')
            if allowed.lower() == 'n':
                return None

        password = input('Password: ')
        data = password.encode() # Encode the password (I guess that this comment is f*cking useless).
        encoded = encryptor.encryptData(key, data) # Encrypt the password with the key.

        with open(f'./pwd/{name}.md', 'w') as pwdFile:
            pwdFile.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encoded}') # Write the encoded password in the destination file.
            print('Password created successfuly!')

        # Clear all sensitive data from memory.
        encryptor.deleteSensitiveData(salt)
        encryptor.deleteSensitiveData(key)
        encryptor.deleteSensitiveData(password)
        encryptor.deleteSensitiveData(data)

    encryptor.deleteSensitiveData(masterPassword) # Remove the master password from the memory.
    input('\nPress [Enter] to continue..')

def removePassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword) # Check if the provided master password is correct.

        if not success:
            print('Incorrect master password!')
        else:
            for file in files:
                passwords.append(file.split('.md')[0]) # Add the password's name (without the file extension) in the list.

            print(f'Available passwords: {', '.join(passwords)}') # Create a text list with all the available passwords.
            name = input('Password\'s name: ')

            if os.path.isfile(f'./pwd/{name}.md'):
                os.remove(f'./pwd/{name}.md')
                print('Password removed successfuly!')
            else:
                print('This password doesn\'t exist!')

    encryptor.deleteSensitiveData(masterPassword) # Remove the master password from memory.
    input('\nPress [Enter] to continue..')

def showPassword():
    files = os.listdir('./pwd')
    passwords = []

    if not files:
        print('No password available!')
    else:
        masterPassword = input('Master password: ')
        success = encryptor.verifyMaster(masterPassword) # Check if the provided master password is correct.

        if not success:
            print('Incorrect master password!')
        else:
            for file in files:
                passwords.append(file.split('.md')[0]) # Add the password's name (without the file extension) in the list.

            print(f'Available passwords: {', '.join(passwords)}') # Create a text list with all the available passwords.
            name = input('Password\'s name: ')

            if os.path.isfile(f'./pwd/{name}.md'):
                with open(f'./pwd/{name}.md', 'r') as pwdFile:
                    content = pwdFile.read()
                    salt, encoded = content.split(':') # Split the salt and the encoded password.
                    salt = base64.urlsafe_b64decode(salt) # Decode the salt with base64.
                    key = encryptor.generateValidKey(masterPassword, salt) # Generate a key for the decryption.
                    password = encryptor.decryptData(key, encoded) # Decode the password with the key.
                    if password:
                        print(f'{name}\'s password: {password}')

                # Clear all sensitive data from memory.
                encryptor.deleteSensitiveData(salt)
                encryptor.deleteSensitiveData(key)
                encryptor.deleteSensitiveData(password)
            else:
                print(f'Password "{name}" doesn\'t exist!')

    encryptor.deleteSensitiveData(masterPassword) # Remove the master password from memory.
    input('\nPress [Enter] to continue..')

def changeMaster():
    current = input('Current master password: ')
    success = encryptor.verifyMaster(current) # Check if the provided master password is correct.

    if not success:
        print('Incorrect master password!\n')
    else:
        new = input('New master password: ')
        salt = os.urandom(16) # Generate a random salt.
        key = encryptor.generateValidKey(new, salt) # Generate a valid key for the encryption.
        encoded = encryptor.encryptData(key, new.encode()) # Encode the new master password.

        with open(f'master.md', 'w') as master:
            master.write(f'{base64.urlsafe_b64encode(salt).decode()}:{encoded}') # Write the new encoded master password in the destination file.
            print('Master password successfuly updated!\n')

        # Clear all sensitive data from memory.
        encryptor.deleteSensitiveData(new)
        encryptor.deleteSensitiveData(salt)
        encryptor.deleteSensitiveData(key)
    input('Press [Enter] to continue..')