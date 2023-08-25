n = int(input())
nums = [*map(int, input().split())]
target = sorted(nums)

def add_targets(set_1, values_1):
    for i, item in enumerate(nums):
        if item in values_1:
            set_1.add(i + 1)
    return set_1


def fill_set(set_1):
    """Fills a set of indices with more valid indices until it is of length n // 2"""
    i = 0
    while len(set_1) < n // 2:
        if not(i + 1 in set_1):
            set_1.add(i + 1)
        i += 1
    return set_1

def apply_ops(nums, indices):
    """Processes an instruction to sort half of the array and updates the array"""
    indices = sorted([*map(lambda x : x - 1, indices)])
    values = sorted([*map(lambda x : nums[x], indices)])
    for index, value in zip(indices, values):
        nums[index] = value
    return nums 

# Numbers in the bottom quarter, plus the bottom quarter places
values_1 = set(target[:n//4])
set_1 = set(range(1, n // 4 + 1))
set_1 = add_targets(set_1, values_1)
set_1 = fill_set(set_1)

nums = apply_ops(nums, set_1)

# Numbers in the top quarter, plus the top quarter places
values_2 = set(target[3 * n//4:])
set_2 = set(range(3 * n//4 + 1, n + 1))
set_2 = add_targets(set_2, values_2)
set_2 = fill_set(set_2)

# Middle 2 quarters
set_3 = range(n // 4 + 1, 3 * n // 4 + 1)

print(3)
print(" ".join(map(str, set_1)))
print(" ".join(map(str, set_2)))
print(" ".join(map(str, set_3)))

