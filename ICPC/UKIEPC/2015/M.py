from fractions import Fraction
M,N = map(int, input().split())
ts = [*map(int, input().split())]
ds = [*map(int, input().split())]

res = set()
for n in range(N - M + 1):
    dd = ds[n + 1] - ds[n]
    td = ts[1] - ts[0]
    f = Fraction(dd / td)

    ok = True
    for m in range(1,M - 1):
        dd = ds[n + m + 1] - ds[n + m]
        td = ts[m + 1] - ts[m]
        
        if Fraction(dd / td) != f:
            ok = False
            break
    if ok:
        res.add(ds[n + 1] - ds[n])

print(len(res))
print(" ".join(map(str,sorted(list(res)))))
