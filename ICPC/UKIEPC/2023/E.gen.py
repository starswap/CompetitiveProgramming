import random
alpha = "ABCDEFGHIJKLMNOPQRTSUVWXYZ!?@*"
MAX = 20
sub = random.sample(alpha, random.randint(1, MAX))
print("".join(sub))
D = []
for i in range(len(sub)):
    D.append([])
    for j in range(i, len(sub)):
        D[-1].append(random.randint(-1000000, 1000000))
        
print("\n".join(map(lambda x: " ".join(map(str, x)), D)))