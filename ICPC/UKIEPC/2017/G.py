aX0, aY0, aZ0, aX1, aY1, aZ1 = map(int, input().split())
bX0, bY0, bZ0, bX1, bY1, bZ1 = map(int, input().split())

class Robot:
    def __init__(self, x, y, z, targX, targY, targZ, aside):
        self.x = x
        self.y = y
        self.z = z
        self.targX = targX
        self.targY = targY
        self.targZ = targZ
        self.aside = aside

    def output(self):
        return f"({self.x}, {self.y}, {self.z})"
    
    def done(self):
        return (self.x == self.targX) and (self.y == self.targY) and (self.z == self.targZ)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.z == other.z

    def next(self):
        if self.aside:
            return self.moveBack() 
        else:
            if (self.x != self.targX):
                dx = (self.targX - self.x)
                return Robot(self.x + dx // abs(dx), self.y, self.z, self.targX, self.targY, self.targZ, None)
            elif (self.y != self.targY):
                dy = (self.targY - self.y)
                return Robot(self.x, self.y + dy // abs(dy), self.z, self.targX, self.targY, self.targZ, None)
            elif (self.z != self.targZ):
                dz = (self.targZ - self.z)
                return Robot(self.x, self.y, self.z + dz // abs(dz), self.targX, self.targY, self.targZ, None)
            else:
                return self
    
    def moveAside1(self):
        if (self.x != self.targX):
            if self.y == 1000:            
                return Robot(self.x, self.y - 1, self.z, self.targX, self.targY, self.targZ, [(0, 1, 0)])
            else:
                return Robot(self.x, self.y + 1, self.z, self.targX, self.targY, self.targZ, [(0, -1, 0)])
        elif (self.y != self.targY):
            if self.z == 1000:
                return Robot(self.x, self.y, self.z - 1, self.targX, self.targY, self.targZ, [(0, 0, 1)])
            else:
                return Robot(self.x, self.y, self.z + 1, self.targX, self.targY, self.targZ, [(0, 0, -1)])
        else:
            if self.y == 1000:            
                return Robot(self.x, self.y - 1, self.z, self.targX, self.targY, self.targZ, [(0, 1, 0)])
            else:
                return Robot(self.x, self.y + 1, self.z, self.targX, self.targY, self.targZ, [(0, -1, 0)])
         

    def moveAside2(self):
        if (self.x != self.targX):
            if self.z == 1000:  
                return Robot(self.x, self.y, self.z - 1, self.targX, self.targY, self.targZ, [(0, 0, 1)])
            else:
                return Robot(self.x, self.y, self.z + 1, self.targX, self.targY, self.targZ, [(0, 0, -1)])
        elif (self.y != self.targY):
            if self.x == 1000:
                return Robot(self.x - 1, self.y, self.z, self.targX, self.targY, self.targZ, [(1, 0, 0)])
            else:
                return Robot(self.x + 1, self.y, self.z, self.targX, self.targY, self.targZ, [(-1, 0, 0)])
        else:
            if self.x == 1000:            
                return Robot(self.x - 1, self.y, self.z, self.targX, self.targY, self.targZ, [(1, 0, 0)])
            else:
                return Robot(self.x + 1, self.y, self.z, self.targX, self.targY, self.targZ, [(-1, 0, 0)])

    def moveBack(self):
        return Robot(self.x + self.aside[0][0], self.y + self.aside[0][1], self.z + self.aside[0][2], self.targX, self.targY, self.targZ, self.aside[1:])

a = Robot(aX0, aY0, aZ0, aX1, aY1, aZ1, None)
b = Robot(bX0, bY0, bZ0, bX1, bY1, bZ1, None)

while not(a.done()) or not(b.done()):
    print(a.output() + " " + b.output())
    if a.next() == b and b.next() == a or a.next() == b.next():        
        a = a.moveAside1() # swapping
        b = b.next()
        print(a.output() + " " + b.output())
        a = a.moveAside2()
        b = b.next()
    else:
        a = a.next()
        b = b.next()

print(a.output() + " " + b.output())

