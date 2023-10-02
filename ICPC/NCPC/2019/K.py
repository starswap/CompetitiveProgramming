n, m, s, d = map(int, input().split())
free = sorted(zip(map(int,input().split()), range(s)))
remaining = n
used = [0 for i in range(s)]
for (used_amt, i) in free:
    free_amt = d - used_amt
    put_in = min(free_amt, remaining)
    used[i] += put_in
    remaining -= put_in
    
    if remaining == 0:
        break

tot = 0
for i in range(s):
    if used[i] == 0:
        tot += sum([a for (a,b) in free if b == i])

if tot < m :
    print("impossible")
else:
    print(" ".join(map(str, used)))