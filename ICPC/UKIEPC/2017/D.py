swaps = []
array = list(input())

def solve():
    global array

    new = sorted(array)
    for i, item in enumerate(new):
        for j, item2 in enumerate(array[::-1]):
            if (item2 == item):
                k = len(array) - 1 - j
                if (i != k):
                    swaps.append((i, k))
                temp = array[i]
                array[i] = array[k]
                array[k] = temp

                break
 
solve()
for (a,b) in swaps[::-1]:
    print(max(a + 1,b + 1), min(a + 1,b + 1))
