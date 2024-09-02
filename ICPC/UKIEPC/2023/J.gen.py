from itertools import product

N = 1000000

def print_time(total_mins):
    mins = total_mins % 60
    total_hours = total_mins // 60
    hours = total_hours % 24
    days = total_hours // 24 
    return f"{days}d{hours:02}:{mins:02}"


print(N)
codes = [*product("abcdefghijklmnopqrstuvwxyz", repeat=5)]

for i in range(N):
    print(f"{''.join(codes[i])} {print_time(i)} {''.join(codes[i+1])} {print_time(i+1)}")

print(N)
print(*[i + 1 for i in range(N)])
