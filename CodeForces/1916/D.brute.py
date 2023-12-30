from collections import Counter
# Brute force checker for intuition
# We suspect there is something suspicious about the fact that 1690000000 is such a
# popular digit set. So try to generate squares with those digits.
# This yields the method implemented in D.

def is_square(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x * x == n

counter = Counter()
for l in range(1, 101, 2):
    nums = []
    cnt = 0 
    for onePos in range(l):
        for sixPos in range(l):
            if onePos == sixPos:
                continue
            for ninePos in range(l):
                if ninePos == sixPos or ninePos == onePos:
                    continue
                if not 0 in (onePos, ninePos, sixPos):
                    continue
                number = [0] * l
                number[onePos] = 1
                number[sixPos] = 6
                number[ninePos] = 9
                if is_square(int("".join(map(str,number)))):
                    nums.append("".join(map(str,number)))
                    cnt += 1
    print(f"For {l} found: {cnt >= l}")
    print("\n".join(nums))