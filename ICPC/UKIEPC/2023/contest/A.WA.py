

MAXWORDS = 100

def dom(a,b):
    if abs(MAXWORDS-a[0]) < abs(MAXWORDS-b[0]):
        #print(a, "DOMS", b)
        return a[1] >= b[1]
    elif abs(MAXWORDS-a[0]) == abs(MAXWORDS-b[0]):
        return a[1] > b[1]
    return False
def brute(essays):
    state = [0]*len(essays)
    rank = [1]*len(essays)
    r = 1
    done = 0
    comps = 0
    while done < len(essays):
        for i in range(len(essays)):
            if state[i] == 0:
                for j in range(i+1, len(essays)):
                    if state[j] == 0:
                        comps += 1

                        if dom(essays[i], essays[j]):
                            state[j] = 1
                        elif dom(essays[j], essays[i]):
                            state[i] = 1
                            break
            if state[i] == 0:
                state[i] = 2
                rank[i] = r
                done += 1
        for j in range(len(essays)):
            if state[j] == 1:
                state[j] = 0
        r += 1
    return comps

from random import randint

print(60*60*3)
essays = list(reversed([(100+i, 100-i) for i in range(60)]))
essays2 = [(randint(1,MAXWORDS), randint(1, 1000)) for i in range(60)]

print(brute(essays))
print(brute(essays2))