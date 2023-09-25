T = int(input())

def can(single, double, decker, amt):
    allSingles = decker * single
    allDoubles = (decker // 2 + 1) * double
    if decker % 2 == 0:
        combo = (decker // 2 - 1) * double + 2 * single
    else:
        combo = (decker - 1) // 2 * double + single
    return allSingles <= amt or allDoubles <= amt or combo <= amt 

for t in range(T):
    A, B, C = map(int, input().split())

    lo = 0 # in
    hi = 1000000000000000000 # out
    while hi - lo > 1:
        
        mi = (lo + hi) // 2
        if (can(A, B, mi, C)):
            lo = mi
        else:
            hi = mi
    print(f"Case #{t + 1}: ", end="")
    print(lo)