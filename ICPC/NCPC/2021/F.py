from itertools import islice
ALPHA = "abcdefghijklmnopqrstuvwxyz"
res = [*islice((ALPHA[i] + ALPHA[j] for i in range(26) for j in range(26)), 64)]

def get_score(x):
    score = 0
    for i in range(10):
        if ((1 << i) & x):
            score += 1
    return score

K = 3
N = 4
MASK = (1 << N) - 1
P = 0.7

def ans(x):

    
    if (get_score(x) >= K):
        return 0
    didnt = ((x & MASK) << 1)
    did = didnt + 1
    if get_score(did) >= K:
        return f"1 + (1 - p) * {res[didnt]}"
    else:
        return f"1 + p * {res[did]} + (1 - p) * {res[didnt]}" 

for i in range(64):
    print(f"{res[i]} = {ans(i)}")