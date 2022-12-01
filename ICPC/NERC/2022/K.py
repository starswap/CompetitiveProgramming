N = int(input())
vals = [list(map(int,input().split())) for i in range(N)]
print(sum(map(sum,vals)) - min([vals[i][N-1-i] for i in range(N)]))
