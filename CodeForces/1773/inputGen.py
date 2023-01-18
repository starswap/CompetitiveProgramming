import random
with open("input.txt","w") as f:
    f.write("1")
    f.write("100000")
    nums = [*range(1,100001)]
    random.shuffle(nums)
    f.write(" ".join(map(str,nums)))