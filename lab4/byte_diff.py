#!/usr/bin/env python3
import hashlib

def bit_diff(hex1, hex2):
    hex1 = int(hex1, 16)
    hex2 = int(hex2, 16)
    and_str = hex1 & hex2
    bin_str = str(bin(and_str))[2:]
    diff = 0
    for char in bin_str:
        if char == '0':
            diff += 1
    return(diff)


normal = "this is a hash message"
alter = "this ir a hash message"

md5_norm = hashlib.md5(normal.encode()).hexdigest()
md5_alt = hashlib.md5(alter.encode()).hexdigest()

sha256_norm = hashlib.sha256(normal.encode()).hexdigest()
sha256_alt = hashlib.sha256(alter.encode()).hexdigest()

print(bit_diff(md5_norm, md5_alt))
print(bit_diff(sha256_norm, sha256_alt))