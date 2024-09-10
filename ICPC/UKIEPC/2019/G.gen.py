import random

# Generates two identical trees with different labelling - should expect
# the same number of signs needed for both
# And furthermore the hashes for corresponding nodes
# should be the same. Checked by G.check.py

N = 300000
edges = []
edges2 = []
mapping = [i for i in range(N)]
random.shuffle(mapping)

for i in range(1, N):
    join_to = random.randint(0, i - 1)
    edges.append((i, join_to))
    edges2.append((mapping[i], mapping[join_to]))
                  
with open("input_1.txt", "w") as f:
    f.write(f"{N}\n")
    for u, v in edges:
        f.write(f"{u + 1} {v + 1}\n")

with open("input_2.txt", "w") as g:
    g.write(f"{N}\n")
    for u, v in edges2:
        g.write(f"{u + 1} {v + 1}\n")

with open("mapping.txt", "w") as h:
    h.write(f"{' '.join(map(str, mapping))}\n")
