# def solve()

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        N = int(input())
        nums = [*map(int, input().split())]

        score = 0
        even = (nums[0] % 2 == 0)
        for item in nums[1:]:
            if even == (item % 2 == 0):
                score += 1
            else:
                even = item % 2 == 0
        
        print(score)
            

