from itertools import permutations, combinations, chain
N, S = map(int, input().split())
nums = map(int, input().split())
best_so_far = 0

def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

def findsubsets(S):
    return chain(*map(permutations, powerset(S)))

count = 1
for perm in findsubsets(nums):
    count += 1
    spare_space = 0
    curr = 1
    lp = list(perm)
    # lp = [6, 5, 4, 6, 3, 4, 8]
    for num in lp[1:-1]:
        overhang = (num % 3)
        # print(curr)
        if overhang <= spare_space:
            curr += num // 3
            spare_space = 0
        else:
            curr += (num + (3 - 1)) // 3
            spare_space = 3 - overhang
    # print(curr)
    if curr <= S - 1:
        # print("ok")
        if (len(lp) == 7):
            print(lp)
        best_so_far = max(best_so_far, len(lp))
    # break
print(best_so_far)
# print(count)