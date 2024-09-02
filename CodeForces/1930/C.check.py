from itertools import product

def f(s):

    if (len(s)) == 0:
        return 0
    # print(s)

    ans = (len(s) + 2) // 3
    for i in range(len(s)):
        if s[i] == "0":
            ans = min(ans, f(s[:i]) + f(s[i + 1:]))
    return ans
    # i = 0
    # while i < len(s) and s[i] == "0":
    #     i += 1
    # j = len(s) - 1
    # while j >= 0 and s[j] == "0":
    #     j -= 1

    # s = s[i:j + 1]
    # i = 0
    # while i < len(s) - 1 and not (s[i] == "0" and s[i + 1] == "0"):
    #     i += 1

    # if i == len(s) - 1:
    #     return (len(s) + 2) // 3
    # else:
    #     # print("----")
    #     # print(i)
    #     # print(s)
    #     # print(len(s) - 1)
    #     # print("----")
    #     left = s[:i]
    #     right = s[i + 2:]

    #     return min((len(s) + 2) // 3, f(left) + f(right))

def is_compat(p, q):
    for i in range(len(p)):
        okThisI = False
        for l in range(i + 1):
            for r in range(i, len(p)):
                subs = q[l : r + 1]
                if subs.count(p[i]) >= len(subs) / 2:
                    okThisI = True
        if not okThisI:
            return False
    return True

def f_brute(s):
    best = 100000
    bestQ = ""
    for q in product("01", repeat=len(s)):
        if is_compat(s, q):
            if q.count("1") < best:
                best = min(best, q.count("1"))
                bestQ = q
    return (best, bestQ)
# print(is_compat("01110", "00100"))
# print(f_brute("00000"))

# print(f("1010101"))
# print(f_brute("1010101"))

for i in range(10):
    for item in product("01", repeat=i):
        string = "".join(item)
        if f(string) != f_brute(string)[0]:
            print(string)
            print(f(string))
            print(f_brute(string))
    # print(i)