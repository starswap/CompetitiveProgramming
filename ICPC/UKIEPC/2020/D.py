n = int(input())
nums = map(int, input().split())
print("yes" if sum(nums) % 3 == 0 else "no")