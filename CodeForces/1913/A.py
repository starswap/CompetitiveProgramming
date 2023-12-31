T = int(input())
for t in range(T):
    string = input()
    done = False
    for i in range(1,len(string)):
        a = string[:i]
        b = string[i:]
        if b[0] != '0' and int(a) < int(b):
            print(a, b)
            done =True
            break
    if not done:
        print(-1)