from Crypto.Protocol.KDF import PBKDF2
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
import base64
import ctypes

def generateValidKey(password: str, salt: bytes) -> bytes:
    # Create a key in 32 bytes with a password, a salt, using PBKDF2.
    return PBKDF2(password, salt, dkLen=32, count=100000, hmac_hash_module=SHA256)

def verifyMaster(input):
    try:
        with open('master.md', 'r') as master:
            content = master.read()
            salt, encoded = content.split(':') # Split the salt and encoded password.
            salt = base64.urlsafe_b64decode(salt) # Decode the salt with base64.
            key = generateValidKey(input, salt) # Generate a key for decryption.
            data = base64.urlsafe_b64decode(encoded) # Decode the data with base64.
            nonce = data[:16]
            tag = data[16:32]
            ciphertext = data[32:]
            cipher = AES.new(key, AES.MODE_EAX, nonce=nonce) # Launch AES with key and nonce.
            decrypted = cipher.decrypt_and_verify(ciphertext, tag) # Decrypt the master password.
            return decrypted.decode('utf-8') == input # Return True only if the input is equal to the decoded password.
    except:
        return False # If the decryption failed, the master password provided is incorrect.

def encryptData(key, data):
    cipher = AES.new(key, AES.MODE_EAX) # Launch AES cypher.
    nonce = cipher.nonce # Launch AES cypher.
    ciphertext, tag = cipher.encrypt_and_digest(data) # Encrypt the data and sign it.
    return base64.urlsafe_b64encode(nonce + tag + ciphertext).decode('utf-8') # Return the encrypted data with base64.

def decryptData(key, data):
    data = base64.urlsafe_b64decode(data) # Decode the base64 encoded data.
    nonce = data[:16]
    tag = data[16:32]
    ciphertext = data[32:]
    cipher = AES.new(key, AES.MODE_EAX, nonce=nonce) # Launch AES cipher with nonce.

    try:
        decrypted = cipher.decrypt_and_verify(ciphertext, tag) # Decrypt the data and verify the integrety.
        return decrypted.decode('utf-8')
    except:
        print('Integrity verification failed!')
        return False

# Remove passwords from the memory.
def deleteSensitiveData(data):
    if isinstance(data, bytes): # If the variable is in bytes.
        ctypes.memset(ctypes.addressof(ctypes.create_string_buffer(data)), 0, len(data))
    else:
        data = str(data).encode()
        ctypes.memset(ctypes.addressof(ctypes.create_string_buffer(data)), 0, len(data))

    data = None # Weak but usefull to have a minimum of protection.