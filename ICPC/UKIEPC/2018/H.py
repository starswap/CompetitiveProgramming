T = int(input())
N = int(input())

PI = 3.1415926535

sizeToAmt = []
for i in range(N):
    amt, size = map(int, input().split())
    sizeToAmt.append([size, amt])

sizeToAmt.sort()
# print(sizeToAmt)
i = 0
t = 0
ptr = 0
while t < T and ptr < N:
    i += 1
    t += PI * 2 * sizeToAmt[ptr][0]
    sizeToAmt[ptr][1] -= 1
    if (sizeToAmt[ptr][1] == 0):
        ptr += 1

if t < T:
    print(i)
else:
    print(i - 1) 
