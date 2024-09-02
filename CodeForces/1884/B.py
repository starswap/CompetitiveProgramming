from bisect import bisect_left, bisect_right
T = int(input())
for t in range(T):
    N = int(input())
    string = input()
    anss = []
    max_poss = (string.count("0"))
    q_len = 0
    ans = 0
    # print(max_poss)
    for i in range(1, N + 1):
        if i > max_poss:
            anss.append(-1)
        else:
            # print("hop")
            # print(N)
            # print(N - i - q_len)
            while string[N - i - q_len] == '1': 
                q_len += 1
            # print(q_len)
            ans += q_len
            anss.append(ans)
    print(" ".join(map(str, anss)))
