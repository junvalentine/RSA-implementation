import time
from Crypto.Util.number import bytes_to_long
from Crypto.PublicKey import RSA
import os

decrypt_times = []
for _ in range(50):
    start_time = time.time()
    key = RSA.generate(2048)
    end_time = time.time()
    decrypt_times.append(end_time - start_time)

# Calculate average decryption time
average_decrypt_time = sum(decrypt_times) / len(decrypt_times)
print(f"Average RSA decryption time: {average_decrypt_time:.6f} seconds")