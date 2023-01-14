N,K = map(int,input().split())
p = list(map(lambda x : int(x) - 1,input().split()))
q = list(map(lambda x : int(x) - 1,input().split()))

charMap = {}
occSet = set()
currChar = ord("a") - 1
for i in range(N):
    if len(occSet) == 0:
        if (currChar < ord("z")):
            currChar += 1
    if (p[i] in occSet):
        occSet.remove(p[i])
    else:
        occSet.add(p[i])
    if (q[i] in occSet):
        occSet.remove(q[i])
    else:
        occSet.add(q[i])
    charMap[p[i]] = chr(currChar)
    charMap[q[i]] = chr(currChar)

if currChar - ord("a") + 1 < K:
    print("NO")
else:
    str = []
    for t in range(N):
        str.append(charMap[t])
    print("YES")
    print("".join(str)) 
     
        


