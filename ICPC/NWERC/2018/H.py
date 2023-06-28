n, c, b = map(int, input().split())
brokens = [*map(lambda x : int(x) - 1, input().split())]

bits = [-1 for _ in range(n)] # default; not set
for i in range(b):
    bits[brokens[i]] = 0 # break brokens

if c % 2 == 1:                    # if odd we need the first one
    bits[0] = 1                   # odd change first to second
    bits[1] = 0
    c -= 1                        # already got one change
else:
    bits[0] = 0

for i in range(c % 2 + 1, n - 1): # carry on from as soon as we can
    if (bits[i] == -1) and c > 0: # not forced and we still need changes
        bits[i] = 1               # greedily make next swap
        bits[i + 1] = 0           # either this is already 0 or unset (can't be 1 as we haven't set 1s that far in array yets)
        c -= 2                    # gives a flip either side. Very effective
    else:
        bits[i] = 0               # either it was already set to 0 or we need to set it to 0 

print(''.join(map(str, bits)))    # output result
