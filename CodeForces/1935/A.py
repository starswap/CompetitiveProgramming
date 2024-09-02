T = int(input())
for t in range(T):
    N = int(input())
    s = input()
    if s[::-1] < s:
        print(s[::-1] + s)
    else:
        print(s)