T = int(input())
string = "Yes"


for t in range(T):
    line = input()
    ok = True
    
    if line[0] in string:
        idx = string.index(line[0])
        
        for char in line[1:]:
            idx += 1
            idx %= len(string)

            if (not(char in string) or idx != string.index(char)):
                ok = False
                break
    else:
        ok = False
        
    print("YES" if ok else "NO")
         
