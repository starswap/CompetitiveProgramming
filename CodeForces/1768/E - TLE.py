# Trying to use Fermat's Little Theorem to compute the inverse every time we need one; too slow. Same algo as E - TLE.py
N,M = map(int, input().split())

MAX_FACT_NEEDED = 3*N
modfact = [1]*(MAX_FACT_NEEDED+1)
print("hop")
for i in range(1,MAX_FACT_NEEDED+1):
    modfact[i] = modfact[i-1]*i % M

def mod_times(*args):
    it = 1
    for item in args:
        it *= item
        it %= M
    return it

def mod_inverse(n):
    return pow(n, M - 2, M) # Fermat's little theorem; because M is prime.

def mod_choose(n,r):
    return modfact[n] * mod_inverse(modfact[r] * modfact[n-r] % M) % M


le0 = 1
le1 = (modfact[2*N] * 2 - modfact[N]) % M
le2 = ((mod_choose(2*N,N) * modfact[N] * modfact[2*N] * 2) % M) - sum(
    [ mod_times(pow(mod_choose(N,i),2,M),modfact[i],mod_choose(2*N - i, N),modfact[N],mod_choose(N,N-i), modfact[N-i],modfact[N])
    for i in range(0, N+1)]
) % M
print("hop")
le3 = modfact[3*N]

print(f"su {((mod_choose(2*N,N) * modfact[N] * modfact[2*N] * 2) % M)}")
print(f"LE0: {le0}")
print(f"LE1: {le1}")
print(f"LE2: {le2}")

num0s = le0
num1s = le1 - le0
num2s = le2 - le1
num3s = le3 - le2

print(f"Num 1s = {num1s}")
print(f"Num 2s = {num2s}")
print(f"Num 3s = {num3s}")
# print(f"au total = {total}")

ans = 0*num0s + 1*num1s + 2*num2s + 3*num3s
print(ans % M)


# num2s = sum(
#     [mod_choose(N,i) *        # pick which of ghi should go to the front
#      mod_choose(N,i) *        # pick which spaces they should go into
#      modfact[i) *             # pick the order in which they should go into the spaces 
#      mod_choose(2*N-i,N) *    # pick from defi which should occupy the final n
#      nb *                     # pick the order they should go into
#      (modfact[2*N-i))         # reorder the remaining acdf
#      for i in range(1,N+1)]
# ) * 2

# 
# modInverse = [1]*(MOD_MAX+1)
# modFact[= [1]*(MOD_MAX+1)

# def prep_inverses():
#     modFact[0] = 1
#     modInverse[0] = 1
#     for i in range(1,MOD_MAX+1):
#         modFact[i] = (modFact[i - 1] * i) % M
    
#     modInverse[MOD_MAX] = pow(modFact[MOD_MAX], M - 2, M) # Fermat's little theorem; because M is prime.

#     for i in range(MOD_MAX,0,-1):
#         modInverse[i-1] = (modInverse[i] * i) % M

# prep_inverses()
# print(modInverse)
# print(modFact[


# def mod_choose(n,r):
#     return (fact(n)//(fact(r) * fact(n-r))) % M
