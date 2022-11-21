T = int(input())

def tensFivesTwos(n):
    amt = [0,0,0]
    while n % 10 == 0 and n != 0:
        amt[0] += 1
        n /= 10
    while n % 5 == 0 and n != 0:
        amt[1] += 1
        n /= 5
    while n % 2 == 0 and n != 0:
        amt[2] += 1
        n /= 2
    return amt

for t in range(T):
    N,M = map(int,input().split())


    (tens,fives,twos) = tensFivesTwos(N)
    # print(tens,fives,twos)
    mult = 1
    while fives < twos and (5 * mult <= M):
        mult *= 5
        fives += 1
    while twos < fives and (2 * mult <= M):
        mult *= 2
        twos += 1

    while 10*mult <= M:
        mult *= 10
    
    if mult == 1:
        print(N*M)
    else:
        for i in range(9,1,-1):
            while i*mult <= M:
                mult *= i
        print(mult*N)


