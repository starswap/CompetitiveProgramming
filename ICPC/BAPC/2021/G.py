BLOCK_SIZE = 16
MOD = 1000000007
A = [58018, 419817, 467405, 76676, 168542, 130899, 112855, 109529, 105539, 321104, 81539, 143665, 486822, 366448, 445912, 111388]

def build_lookup_table():
    reverse_lookup = {}
    for mask in range(1 << BLOCK_SIZE):
        acc = 0
        for j in range(BLOCK_SIZE):
            operation = ((1 << j) & mask) >> j
            if operation == 0:
                acc *= A[j]
            else:
                acc += A[j]
            acc %= MOD

        reverse_lookup[acc] = mask
    return reverse_lookup

def block_to_ops(block):
    ops = ""
    for j in range(BLOCK_SIZE):
        operation = ((1 << j) & block) >> j
        if operation == 0:
            ops += "x"
        else:
            ops += "+"
    return ops

def inverse_known_ops(known_ops, ans):
    for op in known_ops[::-1]:
        if op == "+":
            ans -= 1
            ans += MOD
            ans %= MOD
    return ans

def query(to_output):
    print("? " + " ".join(map(str, to_output)))

def solve_for_blocks(reverse_lookup):
    known_ops = ""
    for i in range(0, n - BLOCK_SIZE + 1, BLOCK_SIZE):
        query([0] * (n - i - BLOCK_SIZE + 1) + A + [1] * (i))
        ans = int(input())
        ans = inverse_known_ops(known_ops, ans)
        known_ops = (block_to_ops(reverse_lookup[ans])) + known_ops
    return known_ops

def solve_small_case(known_ops):
    for i in range(n % BLOCK_SIZE - 1, -1, -1):
        query([0] * (i + 1) + [1] * (n - i))
        ans = int(input())
        ans = inverse_known_ops(known_ops, ans)
        known_ops = ('x' if ans == 0 else '+') + known_ops
    return known_ops

reverse_lookup = build_lookup_table()
n = int(input())
result = solve_for_blocks(reverse_lookup)
result = solve_small_case(result)

print("! " + result)
