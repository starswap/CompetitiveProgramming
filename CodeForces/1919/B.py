T = int(input())
for t in range(T):
    N = int(input())
    a = input()
    
    blocks = []
    score = 0
    last = a[0]
    for item in a:
        if item != last:
            blocks.append(score)
            score = 0
            last = item
        if item == "+":
            score += 1
        else:
            score -= 1
    blocks.append(score)
    num_blocks = len(blocks)
    while num_blocks > 1:
        a = blocks.pop() 
        b = blocks.pop()
        num_blocks -= 1
        blocks.append(a + b)
    print(abs(blocks[0]))