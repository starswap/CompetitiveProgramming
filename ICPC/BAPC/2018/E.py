
def fact(n):
    if n == 0:
        return 1
    else:
        return n * fact(n-1)

def unsorted(n):
    if n == 1:
        return 0
    else: 
        return fact(n) - not_unsorted(n)

def not_unsorted(n):
    if n == 1:
        return 1
    else:
        tot = 0
        for i in range(1, n):
            tot += not_unsorted(i) * unsorted(n - i)
        return tot


# last not first unsorted
print(not_unsorted(4))
print(unsorted(4))