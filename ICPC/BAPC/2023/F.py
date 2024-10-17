N, C = map(int, input().split())
people = [*map(int, input().split())]
in_queue = 0
best_waiting_time = N + 2
best_start = 0
for i, arrivals in enumerate(people):
    in_queue += arrivals
    seconds_wait = (in_queue + 1 + C - 1) // C
    arrival = i + seconds_wait - 1
    if arrival < N and seconds_wait < best_waiting_time:
        best_start = i
        best_waiting_time = seconds_wait
    in_queue -= C
    in_queue = max(0, in_queue)

if best_waiting_time == N + 2:
    print("impossible")
else:
    print(best_start)
