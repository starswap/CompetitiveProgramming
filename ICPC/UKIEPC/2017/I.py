n = int(input())
nums = [*map(int, input().split())]
m = int(input())
print(min(zip(map(lambda x : m % x, nums),nums))[1])
