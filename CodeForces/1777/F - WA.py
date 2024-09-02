def solve(numbers):
    
    best_sum = 0
    current_sum = 0
    maxi = 0
    for i,x in enumerate(numbers):
        if x > maxi:
            new = current_sum ^ maxi
            maxi = x
        else:
            new = current_sum ^ x
        
        if i > 0 and (numbers[i-1] ^ numbers[i] ^ max(numbers[i-1], numbers[i])) > new:
            current_sum = (numbers[i-1] ^ numbers[i] ^ max(numbers[i-1], numbers[i]))
            maxi = max(numbers[i-1], numbers[i])
        else:
            current_sum = new

        best_sum = max(best_sum, current_sum)

    return best_sum


if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        N = int(input())
        nums = [*map(int, input().split())]
        print(solve(nums))
