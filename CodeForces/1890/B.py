T = int(input())
for t in range(T):
    n, m = map(int, input().split())
    s = input()
    t = input()
    
    diffs = set()
    for i in range(n-1):
        if s[i] == s[i + 1]:
            diffs.add(s[i])
    
    if len(diffs) == 0:
        print("Yes")
    else:
        t_good = True
        for i in range(m-1):
            if t[i] == t[i + 1]:
                t_good = False
        if not t_good:
            print("No")
        else: 
            if t[0] in diffs or  t[-1] in diffs:
                print("No")
            else:
                print("Yes")

            


# if S bad - die

# otherwise need to split up all 00 and 11. If S ends are 0 0 will split up 00. 