def large_palindrome_below(n):
    stri = str(n)
    hl = (len(stri) // 2)
    if len(stri) % 2 == 0:
        firstHalf = stri[:hl]
        if int(firstHalf + firstHalf[::-1]) > n:
            if int(stri[hl - 1]) == 0 or int(firstHalf) == 0:
                return int("9" * (len(stri) - 1))
            else:
                firstHalf = firstHalf[:-1] + str(int(stri[hl-1])-1)
        return int(firstHalf + firstHalf[::-1])
    else:
        if stri[hl] == '0':
            return int("9" * (len(stri) - 1))
        return int(stri[:hl] + str(int(stri[hl]) - 1) + stri[:hl][::-1])

def solve(n):
    palindromes = []
    while str(n) != str(n)[::-1]:
        pal = large_palindrome_below(n)
        n -= pal
        palindromes.append(pal)
    
    palindromes.append(n)
    return palindromes

N = int(input())
pals = solve(N)
print(len(pals))
for pal in pals:
    print(pal)