string = input()
n = int(input())
l = 0
r = len(string) - 1
for i in range(n):
    a, b = map(int, input().split())
    l += a
    r = l + b

print(string[l:r])