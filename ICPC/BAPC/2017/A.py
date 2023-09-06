line = input().split()

M = int(line[0])
N = int(line[1])
R = float(line[2])

PI = 3.14159265358979323846

# x = dist_from_edge
# y = dist_from_center

a_x, a_y, b_x, b_y = map(int, input().split())

y_step_cost = R / N

def switch_cost(switch_y, a_x, b_x):
    r = y_step_cost * switch_y
    return abs(a_x - b_x) * PI * r / M

best_dist = 1000000000000000
for switch_y in range(max(b_y, a_y) + 1):
    best_dist = min(best_dist, y_step_cost * abs(a_y - switch_y) + y_step_cost * abs(b_y - switch_y) + switch_cost(switch_y, a_x, b_x))

print(best_dist)