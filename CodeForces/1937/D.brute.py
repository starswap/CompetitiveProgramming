# L = list("<>><<<<<>")
L = "<>><<<<<>><<>><>>"
def naive(startI, L):
    # print(L)
    i = startI
    cnt = 0
    while i >= 0 and i < len(L):
        # print("".join(L))
        # print(" " * (i) + "^")
        if L[i] == ">":
            L[i] = "<"
            i += 1 
        else:
            L[i] = ">"
            i -= 1
        cnt += 1
    return cnt

def preprocess(L):
    N = len(L)
    rL = 1
    runs = []
    for i in range(1, len(L)):
        if L[i - 1] == L[i]:
            rL += 1
        else:
            runs.append((L[i - 1], rL))
            rL = 1
    runs.append((L[N - 1], rL))
    return runs

# def lessNaive(runs, L):
#     seen = 0
#     j = 0

#     for i in range(len(L)):
#         if seen 

#     while seen < startI + 1:
#         seen += runs[j]
#         j += 1
#     seen -= runs[j]
#     j -= 1
#     runs = runs[:j] + [startI + 1 - seen] + [runs[j] - (startI + 1 - seen)] + runs[j:]


print(" ".join(map(str, [naive(i, list(L)) for i in range(len(L))])))
runs = preprocess(L)

print(runs)
# go back and forth once per value in the opposite way run
# 
        

# runs = [1, 2, 5, 1]
