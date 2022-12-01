from math import ceil

def numLessThan(c):
    return ord(c) - ord('a')

MOD = 1000000007

T = int(input())
for t in range(T):
    N,K = map(int, input().split(" "))
    S = input()

    total = 0
    for (i, char) in enumerate(S[:ceil((len(S))/2)]):
        total += numLessThan(char)*pow(K,(ceil((len(S))/2)-i-1),MOD)
        total %= MOD
    
    if (N % 2 == 0 and (S[:N//2] + S[:N//2][::-1]) < S): 
        total += 1
    elif (N % 2 == 1 and (S[:N//2+1] + S[:N//2][::-1]) < S):
        total += 1

    total %= MOD

    print(f"Case #{t+1}: {total}")

