

sq,st,c = list(map(int, input().split()))


ans = 2*sq


if c >= 2:
    ### Use s tiles
    ans += 3+2*st
    c -= 2
ans += (c//2)*3