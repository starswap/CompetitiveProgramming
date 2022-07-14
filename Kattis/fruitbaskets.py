# This implementation uses backtracking to select all subsets up to 200 and then once the subtotal gets to 200 we know we can choose all possible subsets of the remaining items, the sum of whose values can be calculated with a basic formula in the base case. Therefore the max depth is 4.
#I thought that I needed to use Python as the answer would overflow MAX_LONG_LONG but in fact it doesn't; so C++ would have worked fine.

def basketTotal(current,total):
  if (total >= 200):
    n = N-current
    remTotal = partialSums[N-1]-partialSums[current-1] 
    allTotal = 0
    if (n >= 1):
      allTotal += (1<<(n-1))*remTotal
    allTotal += ((1<<n))*total
    return allTotal
  elif (current >= N):
    return 0
  else:
    allTotal = 0
    allTotal += basketTotal(current+1,total + fruitWeights[current]) #take this piece
    allTotal += basketTotal(current+1,total) #don't take this piece
    return allTotal

N = int(input())
fruitWeights = [int(a) for a in input().split()]
partialSums = [0 for n in range(N)]
total = 0
for n in range(N):
  total += fruitWeights[n]
  partialSums[n] = total

print(basketTotal(0,0))
