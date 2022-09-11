import random

ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,;':#~()[]"

TCs = 10000
MIN_LEN = 100
MAX_LEN = 100
PROBLEM_CHANCE = 0.5


random.seed(1000)

for t in range(TCs):
    length = random.randint(MIN_LEN,MAX_LEN)
    string = ""
    for l in range(length):
        string = string + random.choice(ALPHA)
    if (random.random() < PROBLEM_CHANCE):
        posnOfProblem = random.randint(0,len(string))
        string = string[:posnOfProblem] + "problem" + string[posnOfProblem:] 
    print(string)
