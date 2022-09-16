# The HC official solution claims that there can be only about 35000 vertices in the convex hull, and they provide a program to prove this.
# Rather than use their program, I tried to write my own to understand the investigative process:

# Using their algorithm, we want:
# Maximum number of vectors (i.e. smallest vectors) with:
# -  total x coordinate 500K
# - total y coordinate 500K
# - No vector is a scalar multiple of another
# We can then produce the maximum vertex convex hull by ordering these vectors to ensure the result is convex.
# 500 000

# This turns out to be a much simpler greedy algorithm than their method. So it's not perfectly accurate but the result it gives is quite close.


def trackVectors():
    ratios = set()
    totalX = 0
    totalY = 0
    INF = 10000000

    def addVector(x,y):
        nonlocal ratios, totalX, totalY
        try:
            ratio = round(x/y,7)
        except ZeroDivisionError:
            ratio = INF
        if not(ratio in ratios):
            ratios.add(ratio)
            totalX += x
            totalY += y
    
    def getTotalX():
        return totalX
    
    def getTotalY():
        return totalY
    
    def getRatios():
        return ratios

    return addVector, getTotalX, getTotalY, getRatios

addVector, getTotalX, getTotalY, getRatios = trackVectors()

#Don't forget we can have vertical vectors
for x in range(0,500001): #won't get anywhere near the max bound
    for y in range(0,x+1): #won't get anywhere near the max bound
        if getTotalX() >= 500000 or getTotalY() >= 500000:
            break
        addVector(x,y)
        addVector(y,x)

    if getTotalX() >= 500000 or getTotalY() >= 500000:
        break

print("Number of vectors in this quadrant is " + str(len(getRatios())-1))
print("Therefore maximum total in CH is " + str((len(getRatios())-1)*4))
print(getTotalX())
print(getTotalY())
# print(sorted(getRatios()))