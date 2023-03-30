import heapq as hp

q = []
hp.heapify(q)

n, h = map(int, input().split())
ns = map(int, input().split())

cts = {}
for n in ns:
    if n in cts:
        cts[n] += 1
    else:
        cts[n] = 1

if len(cts) < h:
    print("impossible")
else:
    for (v, ct) in cts.items():
        hp.heappush(q, (-ct, v))

    while len(q) >= h:
        hand = []
        toReAdd = []
        for i in range(h):
            (ct, v) = hp.heappop(q)
            if ct < -1:
                toReAdd.append((ct + 1, v))
            hand.append(v)

        for item in toReAdd:
            hp.heappush(q, item)
        
        print(" ".join(map(str, hand)))
