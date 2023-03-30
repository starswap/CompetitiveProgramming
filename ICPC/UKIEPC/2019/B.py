N = int(input())

t = int(str(N)[0])
if len(str(N)) > 1 and int(str(N)[1]) >= 5:
    t += 1

while (abs(10 * t - N) < abs(t - N)):
    t *= 10
print(t)
