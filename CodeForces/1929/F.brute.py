from math import comb

def get(i, sum_level, D):
    if sum_level == 0:
        return 1
    else:
        ans = 0
        for j in range(i, D + 1):
            ans += get(j, sum_level - 1, D)
        return ans

def getcomb(sum_level, D):
    return comb(D - 1 + sum_level, sum_level)

print(getcomb(sum_level=2, D=4))

# for a block of length L with difference D we want
# sum level of L and D = D
# in particular this 