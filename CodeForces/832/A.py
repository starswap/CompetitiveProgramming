T = int(input())
for t in range(T):
    n = int(input())
    nums = list(map(int, input().split()))
    set1 = abs(sum(filter(lambda x : x >= 0, nums)))
    set2 = abs(sum(filter(lambda x : x < 0, nums)))
    print(abs(set1 - set2))
