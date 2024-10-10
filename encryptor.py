from Crypto.Protocol.KDF import PBKDF2
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
import base64
import ctypes

def generateValidKey(password: str, salt: bytes) -> bytes:
    # Create a key in 32 bytes with a password and a salt, using PBKDF2 tool.
    return PBKDF2(password, salt, dkLen=32, count=100000, hmac_hash_module=SHA256)

def verifyMaster(input):
    try:
        with open('master.md', 'r') as master:
            salt, encoded = master.read().split(':')
            salt = base64.urlsafe_b64decode(salt) # Decode the salt with base64.
            key = generateValidKey(input, salt) # Generate a valid key for the decryption.
            data = base64.urlsafe_b64decode(encoded) # Decode the data with base64.
            nonce = data[:16]
            tag = data[16:32]
            ciphertext = data[32:]
            cipher = AES.new(key, AES.MODE_EAX, nonce=nonce)
            decrypted = cipher.decrypt_and_verify(ciphertext, tag) # Decrypt the master password and check the signature.
            return decrypted.decode('utf-8') == input
    except:
        return False # If the decryption failed, the master password provided must be incorrect.

def encryptData(key, data):
    cipher = AES.new(key, AES.MODE_EAX)
    nonce = cipher.nonce
    ciphertext, tag = cipher.encrypt_and_digest(data) # Encrypt the data and sign it.
    return base64.urlsafe_b64encode(nonce + tag + ciphertext).decode('utf-8') # Encode it with base64 and return the value in utf-8.

def decryptData(key, data):
    data = base64.urlsafe_b64decode(data) # Decode the data with base64.
    nonce = data[:16]
    tag = data[16:32]
    ciphertext = data[32:]
    cipher = AES.new(key, AES.MODE_EAX, nonce=nonce)

    try:
        decrypted = cipher.decrypt_and_verify(ciphertext, tag) # Decrypt the data and check the signature.
        return decrypted.decode('utf-8')
    except:
        print('Integrity verification failed!')
        return False

def deleteSensitiveData(data):
    data = str(data).encode() # Convert the data in bytes.
    ctypes.memset(ctypes.addressof(ctypes.create_string_buffer(data)), 0, len(data)) # Overwrite the memory at the variable's address.
    data = None