# odd number = impossible
# check if good already. 

done_operations = []
def solve_string(st, ops, start_idx):
    global done_operations
    if ops == 300:
        return False
    elif len(st) == 0:
        return True
    else:
        if st[0] != st[-1]:
            return solve_string(st[1:-1], ops, start_idx + 1)
        else:
            # 
            if st[0] == '0': # add 01 at the end
                done_operations.append(start_idx + len(st))
                return solve_string(st + "01", ops + 1, start_idx)
            else: # add 01 at the beginning
                done_operations.append(start_idx)
                return solve_string("01" + st, ops + 1, start_idx)

T = int(input())
for t in range(T):
    done_operations = []
    n = int(input())
    s = input()
    if n % 2 == 1 or not solve_string(s, 0, 0):
        print("-1")
    else:
        print(len(done_operations))
        print(" ".join(map(str, done_operations)))

# start and end are  0 => impossible