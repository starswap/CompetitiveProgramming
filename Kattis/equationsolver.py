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

EPS = 0.0000001
UNDEF = -1000000000000000000 
N = int(input())
while N != 0:
    eqns = [[*map(float, input().split())]for i in range(N)]
    bs = [*map(float, input().split())]
    for i in range(N):
        eqns[i].append(bs[i])
    
    eqns = gaussian_elimination(eqns)
    ans = [UNDEF for i in range(N)]
    inconsistent = False
    multiple = False
    for i in range(N):
        this_value = eqns[i][N]
        non_zero_values = 0
        last_non_zero = 0
        for j, item in enumerate(eqns[i][:N]):
            if abs(item) > EPS:
                non_zero_values += 1
                last_non_zero = j
        if (non_zero_values > 1):
            multiple = True
        elif non_zero_values == 1:
            ans[last_non_zero] = this_value
        elif (non_zero_values == 0) and abs(this_value) > EPS:
            inconsistent = True

    cols_found = 0
    for item in ans:
        if item != UNDEF:
            cols_found += 1

    if inconsistent:
        print("inconsistent")
    elif multiple or (cols_found < N):
        print("multiple")
    else:
        print(*ans)

    N = int(input())    
