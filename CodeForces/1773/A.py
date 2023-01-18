# Random method according to editorial

import random
import itertools

# [a, b, c, d]
# p = [4, 2, 1, 3]
# q = [3, 1, 3, 4]

# # [1 = a[p[q[0]]],2,3,4]


# if a[p[i]] == 1 then q[1] = i

def second(a, p, N):
    q = [0]*N
    for i, item in enumerate(p):
        q[a[item - 1] - 1] = i + 1
    return q

def noFixed(p):
    for i, item in enumerate(p):
        if i + 1 == item:
            return False
    return True

def bruteSolve(a, N):
    for p in itertools.permutations([*range(1,N+1)]):
        if (noFixed(p) and noFixed(second(a, p, N))):
            return (True, p, second(a, p, N))
    return (False, None, None)

def stochSolve(a, N):
    nums = [*range(1, N+1)]
    for i in range(300):
        random.shuffle(nums)
        if noFixed(nums) and noFixed(second(a, nums, N)):
            return (True, nums, second(a, nums, N)) 
    return (False, None, None)


if __name__ == "__main__":

    T = int(input())
    for t in range(T):
        N = int(input())
        a = [*map(int, input().split())]
        if (N <= 4):
            (poss, p, q) = bruteSolve(a, N)
        else:
            (poss, p, q) = stochSolve(a, N)

        if poss: 
            print("Possible")
            print(" ".join(map(str,p)))
            print(" ".join(map(str,q)))
        else:
            print("Impossible")
            
