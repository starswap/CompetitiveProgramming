from collections import defaultdict
N = int(input())
sentence = input().split()
M = int(input())

correct = defaultdict(lambda : [])
incorrect = defaultdict(lambda : [])
for i in range(M):
    d, e, c = input().split()
    if c == "correct":
        correct[d].append(e)
    else:
        incorrect[d].append(e)

correctWays = 1
totalWays = 1
for word in sentence:
    correctWays *= len(correct[word])
    totalWays *= len(correct[word]) + len(incorrect[word])

if totalWays == 1:
    res = []
    correctFlag = True
    for word in sentence:
        if len(correct[word]) == 0:
            res.append(incorrect[word][0])
            correctFlag = False
        else:
            res.append(correct[word][0])
    
    print(" ".join(res))
    print("correct" if correctFlag else "incorrect")
else:
    print(f"{correctWays} correct")
    print(f"{totalWays - correctWays} incorrect")

