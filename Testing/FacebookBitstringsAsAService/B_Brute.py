import itertools
import os

def assess_bitstring(bitString, conds):
    for (S,E) in conds:
        if (bitString[S:E] != bitString[S:E][::-1]):
            return False
    return True

def run():
    os.system("python B_Gen.py > input.txt")
    os.system("cat input.txt | .\B.exe > output.txt")

run()

with open("input.txt","r") as f:
    with open("output.txt","r") as g:
        passes = 0
        TCs = int(f.readline().strip())

        for t in range(TCs):
            N,M = map(int,f.readline().strip().split())
            conds = []
            for m in range(M):
                X,Y = map(int,f.readline().strip().split())
                conds.append((X-1,Y))

            minDiff = 1000000
            bestBitString = ""
            for bitString in map(lambda it : ''.join(it),itertools.product("01",repeat=N)):
                possible = assess_bitstring(bitString,conds)
                if possible:
                    diff = abs(bitString.count("0") - bitString.count("1"))
                    if  diff < minDiff:
                        minDiff = diff
                        bestBitString = bitString

            
            myAnswer = g.readline().strip().split()[-1]
            possible = assess_bitstring(myAnswer,conds)
            myDiff = abs(myAnswer.count("0") - myAnswer.count("1"))

            if (possible and myDiff == minDiff):
                print(f"Test {t+1} ok! C++ Answer {myAnswer}. Python Answer: {bestBitString}.")
                passes += 1
            elif not(possible):
                print(f"Test {t+1} fail: doesn't meet palindrome requirements. C++ Answer {myAnswer}. Python Answer: {bestBitString}.")
            elif myDiff != minDiff:
                print(f"Test {t+1} fail: not minimum difference. C++ Answer {myAnswer}. Python Answer: {bestBitString}.")
        
        print()
        print(f"Passed: {passes}/{TCs}")
            
            



