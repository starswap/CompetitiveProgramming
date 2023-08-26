import random
import subprocess

for i in range(100):

    MIN_N = 4
    MAX_N = 20 # 100000
    n = random.randint(MIN_N, MAX_N)
    while n % 4 != 0:
        n = random.randint(MIN_N, MAX_N)
    nums = [*range(1, n + 1)]
    random.shuffle(nums)

    input_data = str(n) + "\n" + " ".join(map(str, nums))

    # Run the other script and capture its output
    process = subprocess.Popen(["python", "I.py"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, universal_newlines=True)
    # Send the input data to the subprocess
    output, _ = process.communicate(input=input_data)
    # print(output)

    lines = output.split("\n")
    # print(nums)
    for line in lines[1:]:
        indices = sorted([*map(lambda x : int(x) - 1, line.split())])
        # indices = [*map(lambda x : int(x) - 1, line.split())]

        values = sorted([*map(lambda x : nums[x], indices)])

        for index, value in zip(indices, values):
            nums[index] = value 
        
    if nums != sorted(nums):
        print("FAIL")
        print(input_data)