from math import sqrt
def dist(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)
skx, sky, sox, soy, ekx, eky, eox, eoy = map(int, input().split())
print(max(dist((ekx, eky), (eox, eoy)), dist((skx, sky), (sox, soy))))