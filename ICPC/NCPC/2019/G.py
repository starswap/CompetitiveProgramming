n, m, k = map(int, input().split())

def pointsForG(groupsOfSizeK):
    spare = n - groupsOfSizeK * k
    pointsPerGroupA = spare // m
    pointsPerGroupB = spare // m + 1
    groupA = m - spare % m
    groupB = spare % m

    kPoints = k * (groupsOfSizeK * (groupsOfSizeK + 1)) // 2
    groupBPoints = pointsPerGroupB * (groupsOfSizeK * groupB + groupB * (groupB + 1) // 2)
    groupAPoints = pointsPerGroupA * ((groupsOfSizeK + groupB) * groupA + (groupA * (groupA + 1)) // 2)

    return kPoints + groupAPoints + groupBPoints

# O(m) method from the solutions - remark that once we remove m groups of size k, we have k * m to spread across the m small groups. This makes each small group be of size k and so we can't reduce the number of groups of size k any more.
best = 0
for g in range(max(0, n // k - m), n // k + 1):
    best = max(pointsForG(g), best)
print(best)
