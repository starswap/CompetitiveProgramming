# Modify A.cpp to print W before the output to use this. 

W = int(input())

essays = []
try:
    while True:
        essays.append(tuple(map(int, input().split())))
        assert essays[-1][0] >= 0 and essays[-1][0] <= 10000  
        assert essays[-1][1] >= 0 and essays[-1][1] <= 1000  
except EOFError:
    pass

assert len(essays) == len(set(essays)) # none equal to each other

in_work = set()
postponed = set()
marked = set()

r = 1
N = len(essays)

for i in range(N):
    in_work.add(i)

comps = 0

def dom(a, b):
    wa = abs(W - a[0])
    wb = abs(W - b[0])
    if wa <= wb and a[1] >= b[1] and (wa < wb or a[1] > b[1]):
        return "a"
    elif wb <= wa and b[1] >= a[1] and (wb < wa or b[1] > a[1]):
        return "b"
    else:
        return None

while len(in_work):
    for i in range(N):
        if i in in_work:
            for j in range(i + 1, N):
                if j in in_work:
                    comps += 1
                    comparison_result = dom(essays[i], essays[j])
                    if comparison_result == "a":
                        postponed.add(j)
                        in_work.remove(j)
                    elif comparison_result == "b":
                        postponed.add(i)
                        in_work.remove(i)
                        break 

        if i in in_work:
            in_work.remove(i)
            marked.add(i)

    for essay in postponed:
        in_work.add(essay)
    postponed = set([])

target = N ** 3 / 20
print(f"Comps: {comps}")
print(f"N ^3 / 20: {target}")
print(f"ok? {comps > target}")