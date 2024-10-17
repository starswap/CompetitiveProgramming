N, M, K = map(int, input().split())
nums = sorted([*map(int, input().split())], reverse=True)
done = sum(nums[:M + K])
print(done / sum(nums) * 100)
