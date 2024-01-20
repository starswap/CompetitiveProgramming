T = int(input())
for t in range(T):
    N = int(input())
    As = sorted([*map(int, input().split())])
    
    first = 0
    tris = 0
    for i in range(1, N):
        if As[i - 1] != As[i]:
            first = i
        else:
            number_of_this_one = i - first
            number_of_before = first
            # print(number_of_this_one)
            tris += number_of_before * number_of_this_one
            tris += number_of_this_one * (number_of_this_one - 1) // 2
    print(tris)
    # print("HOP")
        
