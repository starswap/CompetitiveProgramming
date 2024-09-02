

from itertools import permutations, product

def line_case(b1, b2, b3):
    # Put them in a horizontal line; symmetry will take care of the rest
    width = b1[0]+b2[0]+b3[0]
    ## Now take the maximum height for this rotation
    mheight = max([b1[1], b2[1], b3[1]])
    return width * mheight

def triangle_case(b1, b2, b3):
    # Last building is the one on top of the first
    topwidth = b3[0]
    botwidth = b1[0]+b2[0]
    height = max([b1[1], b2[1]])+b3[1]

    return max(topwidth, botwidth)*height

def rot(b):
    return b[1], b[0]

t = int(input())
for i in range(t):
    builds = list(map(int, input().split()))
    b1 = builds[:2]
    b2 = builds[2:4]
    b3 = builds[4:]

    ans = int(1e20)

    for p in product([0,1], repeat=3):
        
        c1 = b1 if not p[0] else rot(b1)
        c2 = b2 if not p[1] else rot(b2)
        c3 = b3 if not p[2] else rot(b3)

        ans = min(ans, line_case(c1, c2, c3))

        ### Now need to try the other buildings in the triangle formation

        for perm in permutations([c1,c2,c3]):
            ### Last building is going to be the one on top
            ans = min(ans, triangle_case(*perm))

    print(ans)

