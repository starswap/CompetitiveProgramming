T = int(input())
def pen(s):
    p = 0
    for i in range(len(s) - 1):
        if s[i] < s[i + 1]:
            p += 1
    return p

for t in range(T):
    N = int(input())
    a = [*map(int, input().split())]
    s = [100000000]
    t = [100000000]
    for item in a:
        if (item <= s[-1]) and (item <= t[-1]) or (item > s[-1] and item > t[-1]):
            if s[-1] < t[-1]:
                s.append(item)
            else:
                t.append(item)
        else:
            if item <= s[-1]:
                s.append(item)
            else:
                t.append(item)
    # print(s)

    # print(t)
    p = pen(s) + pen(t)
    print(p)