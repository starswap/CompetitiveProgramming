def isPrime(x):
    for i in range(2, int(x**0.5)+1):
        if x%i == 0:
            return False
    return True

primes = [i for i in range(2,1000) if isPrime(i)]
#print(primes)

from collections import defaultdict

tree = defaultdict(int)
graph = defaultdict(list)

tree[1] = 1
n = int(input())

for i in range(n-1):
    a,b = list(map(int, input().split()))
    graph[a].append(b)
    graph[b].append(a)


lengths = defaultdict(int)
best_child = defaultdict(int)

def rec(node, par):
    tot = 1
    best_child_her = -1
    for i in graph[node]:
        if i == par:
            continue
        this = rec(i, node) + 1
        if this > tot:
            tot = this
            best_child_her = i
    lengths[node] = tot
    best_child[node] = best_child_her
    return lengths[node]

queue = []
def fill_from(child, curr, prime):
    global queue
    tree[child] = curr * prime
    for v in graph[child]:
        if lengths[v] > lengths[child]:
            continue # ignore parent
        if v != best_child[child]:
            queue.append((curr * prime, v))
        else:
            fill_from(v, curr * prime, prime)

def placement(node):
    global queue
    for v in graph[1]:
        queue.append((1, v))
    
    while len(queue) > 0:
        best_child_score = 0
        best_child = -1 
        best_curr = -1
        best_i = 0
        for i,(curr, child) in enumerate(queue):
            if curr * primes[0] ** lengths[child] > best_child_score:
                best_child = child
                best_child_score = curr * primes[0] ** lengths[child]
                best_curr = curr
                best_i = i
        fill_from(best_child, best_curr, primes[0])
        primes.pop(0)
        queue.pop(best_i)

rec(1, -1)
placement(1)

for i in range(1, n+1):
    assert tree[i] <= int(1000000000*1000000000)
    print(tree[i], end=" ")
print()
 