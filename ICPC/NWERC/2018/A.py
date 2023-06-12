class M:
    """Class for a meta-item"""
    def __init__(self, summ, numm):
        self.sum = summ
        self.num = numm
    
    def avg(self):
        return self.sum / self.num
    
    def merge(self, mm):
        self.sum = self.sum + mm.sum
        self.num = self.num + mm.num

    def __repr__(self):
        return f"M(sum = {self.sum}, num = {self.num})"

def compute(meta_items, nums):
    return sum(map(lambda a, x : (a - x)*(a - x), nums, [m.avg() for m in meta_items for i in range(m.num)]))

def solve(nums):
    meta_items = []
    done = 0
    while done < len(nums) or len(meta_items) >= 2 and meta_items[-1].avg() < meta_items[-2].avg():
        if len(meta_items) >= 2 and meta_items[-1].avg() < meta_items[-2].avg():
            meta_items[-2].merge(meta_items[-1]);
            meta_items.pop()
        elif done < len(nums):
            meta_items.append(M(nums[done], 1))
            done += 1
    return compute(meta_items, nums)

EPS = 0.000000001
N = int(input())
xtarg = []
ytarg = []

for n in range(N):
        x, y = map(int, input().split(" "))
        xtarg.append(x)
        ytarg.append(y)

ans = solve(xtarg) + solve(ytarg)
print(ans)

