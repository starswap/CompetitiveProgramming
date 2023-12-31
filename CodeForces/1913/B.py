from collections import Counter
T = int(input())
def notb(item):
    if item == '0':
        return '1'
    else:
        return '0'
    
for t in range(T):
    string = input()
    cnts = Counter(string)
    done = False
    for i, item in enumerate(string):
        if cnts[notb(item)] == 0:
            print(len(string) - i)
            done = True
            break
        else:
            cnts[notb(item)] -= 1
    if not done:
        print(0)