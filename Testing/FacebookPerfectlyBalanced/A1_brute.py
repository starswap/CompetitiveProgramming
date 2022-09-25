def checkDiff(a_start,a_end,b_start,b_end):
    a_letters = list(string[a_start:a_end+1])
    b_letters = list(string[b_start:b_end+1])
 
    isBLonger = len(b_letters) > len(a_letters)
    totalNotInB = 0

    for letter in a_letters:
        try:
            loc = b_letters.index(letter)
        except ValueError:
            loc = -1

        if loc == -1:
            totalNotInB += 1
        else:
            del b_letters[loc]

    return (totalNotInB == 1 and not(isBLonger)) or (totalNotInB == 0 and isBLonger)

TCs = int(input())
for t in range(TCs):
    string = input()
    Q = int(input())
    queries = []
    for q in range(Q):
        A,B = map(int,input().split())
        queries.append((A-1,B-1))

    totalAlmostPerfect = 0
#    print(partialSums)
    for (A,B) in queries:
        delta = B-A
        if (delta % 2 == 0):
##            one = checkDiff(A,A+delta//2-1,A+delta//2,B)
##            two = checkDiff(A,A+delta//2,A+delta//2+1,B)
##            totalAlmostPerfect += int(one or two)
##            if one or two:
##                print("A ok")
            totalAlmostPerfect += int(checkDiff(A,A+delta//2-1,A+delta//2,B) or checkDiff(A,A+delta//2,A+delta//2+1,B))

    print(f"Case #{t+1}: {totalAlmostPerfect}")
    
