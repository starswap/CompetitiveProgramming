# As per the editorial
# except I may have deviated slightly on le2
# compute the number of permutations with number of moves less than or equal to 0, 1, 2, 3
# use this to get the number of perms with moves equal to 0, 1, 2, 3
# multiply moves by number of perms to get the sum of f(x)

N,M = map(int, input().split())
MAX_FACT_NEEDED = 3*N
modFact = [1]*(MAX_FACT_NEEDED+1)        # modFact[i] = i! % M
modFactInverse = [1]*(MAX_FACT_NEEDED+1) # modFactInverse[i] = (i!) ^ -1 under mod M

def prep_inverses():
    modFact[0] = 1        # 0! = 1 

    # Compute factorials in O(N) bottom-up DP
    for i in range(1,MAX_FACT_NEEDED+1):
        modFact[i] = (modFact[i - 1] * i) % M
    
    # Fermat's little theorem; a^-1 = a^(M-2) because M is prime.
    modFactInverse[MAX_FACT_NEEDED] = pow(modFact[MAX_FACT_NEEDED], M - 2, M) 

    # (n!)^-1 === (n * (n-1)!)^-1
    # (n!)^-1 * (n * (n-1)!) === 1
    # (n!)^-1 * n * (n-1)! === 1
    # (n!)^-1 * n === ((n-1)!)^-1
    # ((n-1)!)^-1 === (n!)^-1 * n
    for i in range(MAX_FACT_NEEDED,0,-1):
        modFactInverse[i-1] = (modFactInverse[i] * i) % M


def mod_times(*args):
    """Compute the product of the arguments mod M"""
    it = 1
    for item in args:
        it *= item
        it %= M
    return it

def mod_choose(n,r):
    """Compute n Choose r (i.e. binomial coefficient), mod M"""
    return mod_times(modFact[n], modFactInverse[r], modFactInverse[n-r])

prep_inverses()

le0 = 1                                     # Trivially; the one where it's already sorted
le1 = (modFact[2*N] * 2 - modFact[N]) % M   # Reorder the first 2n or reorder the second 2n, but we double count ones where only the middle 2n are reordered (so subtract; inclusion - exclusion)

# When we have a double count in the next section, it's because there are the first n in [1..2n] and also the last n in [n+1 to 3n]
# let i be the number of the first n elements present in [n+1..2n]. The numbers of ways of double counting is the sum over all i of:
intersect = sum(
    [ 
        mod_times(
            pow(mod_choose(N,i),2,M),  # choose i of the numbers from 1 to n to place in the middle, and i spaces from the middle n spaces to put them in
            modFact[i],                # choose an order out of i! possible orders of these i items in those i spaces
            mod_choose(2*N - i, N),    # choose a set of n spaces from the remaining 2N-i spaces in positions [n+1 .. 3n] for the items in range 2n+1 to 3n 
            modFact[N],                # choose an order for these out of n! ways
            mod_choose(N,N-i),         # choose n-i spaces from the range [1..n] for the remaining n-i items in range 1 to n
            modFact[N-i],              # choose an order for these remaining n-i items which have values 1 to n and go in positions 1 to n
            modFact[N]                 # the positions in the array of the middle numbers from n+1 to 2n are fixed; now we must order the numbers within those positions; n! ways of doing that.
        )
    for i in range(0, N+1) 
    ]) % M
le2 = ((mod_choose(2*N,N) * modFact[N] * modFact[2*N] * 2) % M) - intersect # Double counting again. As stated in the editorial, <= 2 means that 1-n are in positions 1-2n (2n C n position choices; n! ways to reorder the chosen items; 2n! ways to reorder the others), or 2n+1 to 3n are in n+1 to 3n (same calculation hence the *2), or both. intersect = the double counting.
le3 = modFact[3*N]                           # Try some examples to see that we can always solve the problem in 3 goes or fewer (strategy is to alternate moves - after the first move everything from the chosen side that was wrong is in the middle; after the second move it's in the correct place on the other side, and everything that was wrongly in the other side is now in the middle, and after the third move those ones that were in the middle are now right)

# Compute amount for exactly n rather than <= n
num0s = le0
num1s = le1 - le0
num2s = le2 - le1
num3s = le3 - le2

# Compute and output result
ans = 0*num0s + 1*num1s + 2*num2s + 3*num3s
print(ans % M)

