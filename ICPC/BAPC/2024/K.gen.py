letters = "abccdefghijklmnopqrstuvwxyz"
import random
l = [random.choice(letters) for i in range(5000)]
print(''.join(l))