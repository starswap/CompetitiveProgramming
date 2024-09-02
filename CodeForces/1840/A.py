T = int(input())
for t in range(T):
    N = int(input())
    string = input()
    
    output = ""
    i = 0
    while i < N:
        char = string[i]
        output += char
        i += 1
        while string[i] != char:
            i += 1
        i += 1
    print(output)

