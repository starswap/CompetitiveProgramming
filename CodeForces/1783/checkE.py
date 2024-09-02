with open("output.txt", "r") as out:
    with open("input.txt","r") as inp:
        T = int(inp.readline().strip())
        for t in range(T):
            n = int(inp.readline().strip())
            a = list(map(int, inp.readline().strip().split()))
            b = list(map(int, inp.readline().strip().split()))

            numA = int(out.readline().strip())
            ans = map(int,out.readline().strip().split())
            for i in range(n):
                for k in ans:
                    mono = 0
                    poly = 0
                    d = 0
                    while mono < a[i] and poly < b[i]:
                        mono += (1-d) * k
                        poly += (d) * k
                        d = 1-d
                    
                    if (poly >= b[i]):
                        print(f"FAIL with k = {k}")
                        print(n)
                        print(a)
                        print(b)
