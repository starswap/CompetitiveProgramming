T = int(input())

def get_dig(digit):
    if digit == '0':
        return 10
    else:
        return int(digit)

for t in range(T):
    number = input()
    curr_digit = 1
    total = len(number)
    for digit in number:
        dig = get_dig(digit)
        total += abs(dig - curr_digit)
        curr_digit = dig
    print(total)