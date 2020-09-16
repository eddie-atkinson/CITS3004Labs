#Originally wrote by Russell Ballestrini
#edited by Jin Hong

from string import ascii_letters, digits
from random import shuffle



def random_monoalpha_cipher(pool=None):
    """Generate a Monoalphabetic Cipher
       Returns a dictionary of substitution table randomly generated
    """
    if pool is None:
        pool = ascii_letters + digits
    original_pool = list(pool)
    shuffled_pool = list(pool)
    shuffle(shuffled_pool)
    return dict(zip(original_pool, shuffled_pool))


def key_monoalpha_cipher(key):
    """Generate a Monoalphabetic Cipher using the key provided
       Returns a dictionary of substitution table using the key
    """
    seen = set()
    unique_chars = []
    for char in key:
        if char not in seen:
            unique_chars.append(char)
            seen.add(char)     
    pool = ascii_letters + digits
    last_char = unique_chars[-1]
    before = []
    after = []
    is_before = True
    for char in pool:
        if char != last_char and char not in seen:
            if is_before:
                before.append(char)
            else:
                after.append(char)
        elif char == last_char:
            is_before = False
    final_str = "".join(unique_chars) + "".join(after) + "".join(before) 
    mapping = {}
    for i in range(len(pool)):
        mapping[pool[i]] = final_str[i]
    return mapping
    

def inverse_monoalpha_cipher(monoalpha_cipher):
    """Given a Monoalphabetic Cipher (dictionary) return the inverse."""
    inverse_monoalpha = {}
    for key, value in monoalpha_cipher.items():
        inverse_monoalpha[value] = key
    return inverse_monoalpha


def encrypt_with_monoalpha(message, monoalpha_cipher):
    """Encrypts message using the substitution table monoalpha_cipher"""
    encrypted_message = []
    for letter in message:
        encrypted_message.append(monoalpha_cipher.get(letter, letter))
    return ''.join(encrypted_message)


def decrypt_with_monoalpha(encrypted_message, monoalpha_cipher):
    """Decrypts message using the substitution table monoalpha_cipher"""
    return encrypt_with_monoalpha(
               encrypted_message,
               inverse_monoalpha_cipher(monoalpha_cipher)
           )


# Example usage
message = 'secret message'
# cipher = random_monoalpha_cipher()
cipher =  key_monoalpha_cipher("monopoly")
ciphertext = encrypt_with_monoalpha(message, cipher)
print(ciphertext)
plaintext = decrypt_with_monoalpha(ciphertext, cipher)
print(plaintext)

# print(key_monoalpha_cipher("pineapple"))