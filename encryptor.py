from Crypto.Protocol.KDF import PBKDF2
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
import base64

def generateValidKey(password: str, salt: bytes) -> bytes:
    return PBKDF2(password, salt, dkLen=32, count=100000, hmac_hash_module=SHA256)

def verifyMaster(input):
    try:
        with open(f'./master.md', 'r') as master:
            content = master.read()
            salt, encoded = content.split(':')
            salt = base64.urlsafe_b64decode(salt)
            key = generateValidKey(input, salt)
            cipher = AES.new(key, AES.MODE_EAX, nonce=salt[:16])
            cipher.decrypt(base64.urlsafe_b64decode(encoded))
            return True
    except:
        return False

def encryptData(key, data):
    cipher = AES.new(key, AES.MODE_EAX)
    nonce = cipher.nonce
    ciphertext, _ = cipher.encrypt_and_digest(data)
    return base64.urlsafe_b64encode(nonce + ciphertext).decode()

def decryptData(key, data):
    data = base64.urlsafe_b64decode(data)
    nonce = data[:16]
    ciphertext = data[16:]
    cipher = AES.new(key, AES.MODE_EAX, nonce=nonce)
    return cipher.decrypt(ciphertext).decode()