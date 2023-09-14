def check_sub(smaller, big):
    i = 0
    for j in range(len(big)):
        if smaller[i] == big[j]:
            i += 1
        if i == len(smaller):
            print(i)
            return True
    print(i)
    return False
