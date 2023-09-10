word = input()
n = int(input())
ok_ends = []
for i in range(n):
    rhymers = input().split()
    matches = False
    for rhymer in rhymers:
        if word.endswith(rhymer):
            matches = True
            break
    if matches:
        ok_ends += rhymers
    
P = int(input())
for p in range(P):
    phrase = input()
    matches = False
    for ok_end in ok_ends:
        if phrase.endswith(ok_end):
            matches = True
            break
    print("YES" if matches else "NO")
       