# RECURSION ISSUE

# def internal(n):
    # ans = 0
    # while n != 1:
        # ans (modfact(n-1)*n*(n-1)//2 + (modfact(n)) * internal(n-1)) #% M
M = 1000000007

modfact = [0] * 100001
x = 1
for i in range(100001):
    modfact[i] = x
    x *= (i+1)
    x %= M

# print(modfact[:10])
# def modfact(n):
#     if n == 0:
#         return 1
#     else:
#         return (n * modfact(n-1)) % M


# from itertools import permutations
# def brute(n):
#     score = 0
#     inter = 0
#     exter = 0
#     # print(permutations(n,3))
#     # print("hop")
#     for p in permutations(range(1,n+1),n):
#         print(p)
#         q = p + p[::-1]

#         print(q)
#         for i, ai in enumerate(q):
#             for j, aj in enumerate(q[i:]):
#                 if ai > aj:
#                     jind = i + j
#                     score += 1
#                     if jind < n or i >= n:
#                         inter  += 1
#                     else:
#                         exter += 1

#     print(f"inter: {inter}")
#     print(f"exter: {exter}")

#     return score


def solve(n):
    exter = (modfact[n] * ((n * (n - 1) // 2) % M)) % M
    # inter = (2 * internal(n)) % M

    # print(internal(n))
    # print(f"inter: {inter}")
    # print(f"exter: {exter}")
    return (2 * exter) % M

if __name__ == "__main__":
    T = int(input())
    for t in range(T):
        N = int(input())
        # print("BrutE: " + str(brute(N)))
        print(solve(N))
