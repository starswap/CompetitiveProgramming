import random
with open("E.txt", "w") as f:
    f.write("100\n")
    for i in range(100):
        f.write(f"{random.randint(900000000,1000000000)} {random.randint(900000000,1000000000)}\n")
