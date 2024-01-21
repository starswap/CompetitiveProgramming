def get_score(x):
    score = 0
    for i in range(10):
        if ((1 << i) & x):
            score += 1
    return score

def get_eqns(N, K, P):
    MASK = (1 << N) - 1
    SPACE = (1 << N)

    eqns = [[0 for i in range(SPACE + 1)] for j in range(SPACE)]
    for i in range(SPACE):    
        if (get_score(i) < K):
            didnt = (i << 1) & MASK
            did = didnt + 1
            eqns[i][i] = 1
            eqns[i][did] += - P
            eqns[i][didnt] += - (1 - P)
            eqns[i][SPACE] = 1
        else:
            eqns[i][i] = 1
    return eqns

def row_minus(matrix, i, j):
    for k in range(len(matrix[i])):
        matrix[i][k] -= matrix[j][k]
    return matrix

def row_divide(matrix, i, k):
    for j in range(len(matrix[i])):
        matrix[i][j] /= k
    return matrix

def row_multiply(matrix, i, k):
    for j in range(len(matrix[i])):
        matrix[i][j] *= k
    return matrix

def gaussian_elimination(eqns):
    N = len(eqns)
    M = len(eqns[0])
    row_no = 0

    for i in range(M - 1):
        j = N - 1
        while j > row_no and (eqns[row_no][i] == 0):
            eqns[row_no], eqns[j] = eqns[j], eqns[row_no]
            j -= 1
        if eqns[row_no][i] != 0:
            eqns = row_divide(eqns, row_no, eqns[row_no][i])
            for j in range(N):
                if row_no == j:
                    continue
                factor = eqns[j][i]
                if (factor != 0):
                    eqns = row_divide(eqns, j, factor)
                    eqns = row_minus(eqns, j, row_no)
                    eqns = row_multiply(eqns, j, factor)
            row_no += 1
    return eqns

N, K, P = map(float, input().split()); N = int(N); K = int(K)
es = get_eqns(N, K, P)
es = gaussian_elimination(es)
print(es[0][-1])
