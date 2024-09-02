N, C = map(int, input().split())
songs = [*map(int, input().split())]

total = sum(songs)
m = total % C
base = total // C

ans = []
for i in range(len(songs)):
    last = (i - 1) % len(songs)
    if songs[last] > m:
        ans.append(base - 1)
    else:
        ans.append(base)

print(" ".join(map(str, ans)))