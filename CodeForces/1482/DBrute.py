
def gcd(m, n):
    if n == 0:
        return m
    else:
        return gcd(n, m % n)

if __name__ == "__main__":
    T = int(input())

    for t in range(T):
        N = int(input())
        nums = [*map(int, input().split())]
        i = 0
        changed = True
        deleted = []
        idxs = [i for i in range(N)]

        while changed:
            changed = False
            while i < len(idxs):
                if (gcd(nums[idxs[i]], nums[idxs[(i+1) % len(idxs)]]) == 1):
                    deleted.append(idxs[(i+1) % len(idxs)])
                    idxs.pop((i+1) % len(idxs))
                    changed = True
                i = (i + 1)
            i = 0

        # print(" ".join(map(str,idxs)))
        if len(deleted) == 0:
            print(str(len(deleted)) + " ")
        else:
            print(str(len(deleted)) +" " +  " ".join(map(lambda x : str(x+1),deleted)) + " ")

            
