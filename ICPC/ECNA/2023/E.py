

s = input()


def check(s):
    if s[-1] != "O":
        return False
    for j in s:
        if j not in "EO":
            return False
    for i in range(1, len(s)):
        if s[i] == "O" and s[i-1] == "O":
            return False
    return True

if not check(s):
    print("INVALID")
else:
    for spow in range(2, 1000):
        s = s[::-1]
        can = True
        cur = pow(2, spow)
        for j in range(len(s)):
            if s[j] == "O" and cur != 1:
                if (cur-1) % 3 == 0:
                    cur = (cur-1) // 3
                else:
                    can = False
                    break
            else:
                cur *= 2
            if str(bin(cur))[2:].count("1")  == 1:
                can = False
                break
        if can:
            print(cur)
            break
    else:
        print(1/0)