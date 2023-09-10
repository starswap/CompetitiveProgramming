costOfGrassSeedPerSquareM = float(input())
numberOfFields = int(input())
total = 0
for field in range(numberOfFields):
    dimensions = input().split()
    width = float(dimensions[0])
    height = float(dimensions[1])
    area = width*height
    total += costOfGrassSeedPerSquareM * area # same as total = total+costOfGra...
print(total)
