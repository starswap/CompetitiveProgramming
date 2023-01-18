import copy

def factUpTo26(N):
    nums = []
    for i in range(1,min(N+1,27)):
        if (N % i == 0):
            nums.append(i)
    return nums

T = int(input())
for t in range(T):
    N = int(input())
    string = input()
    counts = {}
    
    for c in string:
        if c in counts:
            counts[c] += 1
        else:
            counts[c] = 1
    
    nums = sorted(counts.items(), key=lambda x : x[1])

    best = 100000000000
    bestTimesEach = 0
    bestTempNums = []

    for f in factUpTo26(N):
        # print(f)

        timesEach = N // f
        tempNums = copy.copy(nums)    # copy

        # remove any extra letters
        if (len(nums) - f > 0):
            ops = sum(map(lambda x : x[1], tempNums[:len(nums) - f]))  # cost to 0 out some letters 
            # print(ops)
            del tempNums[:(len(nums) - f)]
        else:
            ops = 0
            # print(ops)

        missingLetts = set("abcdefghijklmnopqrstuvwxyz")
        
        # add some more letters if we are short of letters
        for (l, t) in tempNums:
            missingLetts.remove(l)
        
        # print(missingLetts)
        for i in range(f - len(tempNums)):
            tempNums.insert(0, (missingLetts.pop(), 0 ))
        
        # print(tempNums)
        # print(timesEach)
        for (l, c) in tempNums:
            ops += abs(c - timesEach)    # cost to set to the correct value
        
        # print(ops)
        # print("---------")
        if ops // 2 < best:
            best = ops // 2
            bestTimesEach = timesEach 
            bestTempNums = copy.copy(tempNums)       


    finalCounts = {}
    for (l, c) in bestTempNums:
        finalCounts[l] = c

    output = ""
    # print(bestTimesEach)
    # print("-----")
    # print(bestTempNums)
    # for char in string:
    #     if not(char in finalCounts):
    #         finalCounts[char] = 0

    # print("--------------")

 #   seen = {l:0 for (l, c) in finalCounts.items()}
    for char in string:
        # print(char)
        # print(finalCounts)
        if not(char in finalCounts) or finalCounts[char] > bestTimesEach :#or seen[char] == finalCounts[char]:  # exists too many times
            # print("op1")
            if char in finalCounts:
                finalCounts[char] -= 1
            newLett = min(finalCounts.items(), key=lambda x : x[1])[0]
            finalCounts[newLett] += 1
            output += newLett
        # elif finalCounts[char] < bestTimesEach:
        #     # print("op2")
        #     finalCounts[char] += 1
        #     newLett = max(finalCounts.items(), key=lambda x : x[1])[0]
        #     finalCounts[newLett] -= 1
        #     output += newLett
        else:
            # print("op3")
            output += char
    print(best)
    print(output) 

            



    # for all factors f of the number N up to 26
    #    consider having f distinct letters, N/f times each
    #    iterate over the numbers and calculate the total delta,
    #    then divide by 2 as this is the number of changes
    # for each letter in the word
    #     if it needs to be increased, swap it for a letter that needs to be
    #     decreased and update that 

        