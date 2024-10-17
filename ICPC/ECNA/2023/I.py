N = int(input())

for n in range(N):
    old = input()
    i = 10
    S = 0
    num_int = 0
    for d in old:
        if d != '-':
            if d == 'X':
                d = 10
            S += i * int(d)
            i -= 1
            num_int += 1
    
    if S % 11 != 0:
        print("invalid")
    elif num_int != 10:
        print("invalid")
    elif old[-1] == '-' or old[0] == '-' or '--' in old:
        print("invalid")
    elif old.count('-') == 3 and not(old[-2]) == '-':
        print("invalid")
    elif old.count('-') > 3:
        print("invalid")
    elif 'X' in old[:-1]:
        print("invalid")
    else:
        new = "978-" + old[:-1] 
        S = 0
        i = 1
        for d in new:
            if d != '-':
                S += i * int(d)
                if i == 1:
                    i = 3
                else:
                    i = 1
        checksum = str(10 - (S % 10))
        if checksum == "10":
            checksum = "0"
        print(new + checksum) 
