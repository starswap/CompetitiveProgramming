N = int(input())
print(sum(map(lambda x : 2 if x == "0" else 1 / int(x),input().split())))