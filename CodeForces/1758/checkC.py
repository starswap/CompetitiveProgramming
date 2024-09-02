with open("output.txt","r") as f:
    for line in f:
        # print(line)
        vals = list(map(int,line.strip().split()))
        # print(vals)
        if (vals == [-1]):
            continue

        n = len(vals)
        for i in range(1,n):
            if vals[i-1] % i != 0:
                print("fail")
                print(vals)

        if vals[n-1] != 1:
            print("fail1")
            print(vals)
        
            