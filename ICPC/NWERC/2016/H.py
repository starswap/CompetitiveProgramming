def gray_code_pos(bstring):
    n = len(bstring)
    if n == 0:
        return 0
    elif bstring[0] == '0':
        return gray_code_pos(bstring[1:])
    else:
        return (1 << n) - 1 - gray_code_pos(bstring[1:])
        
_, a, b = input().split()

print(gray_code_pos(b) - gray_code_pos(a) - 1)