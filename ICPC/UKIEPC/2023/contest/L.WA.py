
H1, D1, T1 = map(int, input().split())
H2, D2, T2 = map(int, input().split())

events = []
t = 0.5

for i in range(1005):
    events.append((t, 1))
    t += T1
t = 0.5
for j in range(1005):
    events.append((t, 2))
    t += T2
events.sort()

def process_shot(shooter):
    global H1, H2, D1, D2
    if shooter == 1:
        H2 -= D1
    else:
        H1 -= D2

idx = 0
while H1 > 0 and H2 > 0:
    process_shot(events[idx][1])
    idx += 1
    # print("H1 " + str(H1))
    # print("H2 " + str(H2))

while idx < len(events) - 1 and events[idx][0] == events[idx + 1][0]:
    process_shot(events[idx][1])
    idx += 1
process_shot(events[idx][1])

if H1 <= 0 and H2 <= 0:
    print("draw")
elif H1 <= 0:
    print("player two")
else:
    print("player one")