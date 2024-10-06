import string
import random

def generatePassword():
    while True:
        length = input('Password length: ')

        if not length.isnumeric:
            print('Please, enter a number!', end = '\n\n')
        elif int(length) < 12:
            print('We don\'t recommend to generating a password under 12 characters.', end = '\n\n')
        elif int(length) > 100:
            print('The password\'s length is too high!', end = '\n\n')
        else:
            length = int(length)
            break

    characters = string.ascii_letters + string.digits + string.punctuation # Set all the characters in this list.
    password = ''

    for _ in range (length):
        randomCharacter = random.choice(characters)
        password += randomCharacter

    print(f'Generated password: {password}')
    input('\nPress [Enter] to continue..')