
def fact(N):
    i = 1
    facts = []
    while i*i <= N:
        if (N % i == 0):
            facts.append((i, N // i))
        i += 1
    return facts

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        N = int(input())
        a = list(map(int, input().split()))

        goodXs = [set() for i in range(N)]
        validXs = set()
        for i in range(N): # 50
            for j in range(i): # 50
                for (l, r) in fact(a[i] - a[j]): # sqrt(N)
                    if ((l + r) % 2) == 0: 
                        u = (l + r) // 2
                        v = (r - l) // 2
                        x = v * v - a[j]

                        if (x >= 0):
                            goodXs[i].add(x)
                            goodXs[j].add(x)
                            validXs.add(x)

        best = 0
        for x in validXs:
            curr = 0 
            for ind in goodXs:
                if x in ind:
                    curr += 1
            best = max(best, curr)
        if len(validXs) == 0:
            print(1)
        else:
            print(best)

