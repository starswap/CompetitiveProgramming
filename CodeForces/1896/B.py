T = int(input())
for t in range(T):
    N = int(input())
    letts = input()
    As = letts.count("A")
    seenAs = 0
    firstA = letts.find("A")
    done = False
    for i,b in enumerate(letts[::-1]):
        if seenAs == As:
            print(0)
            done = True
            break
        if b == 'B':
            print(N - 1 - i - firstA)
            done = True
            break
        else:
            seenAs += 1
    if not done:
        print(0)