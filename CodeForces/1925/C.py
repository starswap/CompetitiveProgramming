T = int(input())
for t in range(T):
    N, K, M = map(int, input().split())
    S = input()
    ptr = 0
    
    string = []
    while ptr < M:
        seen = set()
        while len(seen) < K and ptr < M:
            seen.add(S[ptr])
            ptr += 1
        if len(seen) == K:
            string.append(S[ptr - 1])
            seen.clear()
    
    if len(string) >= N:
        print("YES")
    else:
        print("NO")
        for i in range(K):
            if (chr(ord('a') + i)) not in seen:
                char = chr(ord('a') + i)

        while len(string) < N:
            string.append(char)
        print("".join(string))
