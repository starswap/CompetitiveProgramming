T = int(input())

def solve(arr):
    if (len(arr)) == 0:
        yield set()
    for i, item in enumerate(arr):
        for res in solve(arr[:i] + arr[i + 1:]):
            res.add(item + i + 1)
            yield res

for t in range(T):
    N = int(input())
    A = [*map(int, input().split())]
    ans = sorted(map(lambda x : sorted(list(x),reverse=True), solve(A)), reverse=True)
    print(*(ans[0]))
