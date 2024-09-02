from itertools import product

from string import ascii_lowercase


n = int(input())

wines = [float(input()[:-1]) for i in range(n)]


d = {0.75:"standard", 15:"nebuchadnezzar", 12:"balthazar"}
wines_set = list(set(wines))



done =0
for prod in product(ascii_lowercase, repeat=12):
    if wines[done] not in d:
        d[wines[done]] = "".join(prod)
    done += 1
    if done == n:
        break

for wine in wines:
    print(d[wine])
