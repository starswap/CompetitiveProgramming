S = int(input(), 2)
D = int(input(), 2)
M = int(input(), 2)

for i in range(10000000):
    if M == 0:
        print(str(bin(i))[2:])
        break
    M //= 2
    if i % D == D - 1:
        M += S
else:
    print("Infinite money!")
