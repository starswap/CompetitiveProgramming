import sys
from collections import defaultdict

MAX_N = 3005

# total nombre d'usages par nom/prénom
par_nom = defaultdict(int)
par_prenom = defaultdict(int)

# pour éviter de revoir le même élément plusieurs fois 
vu = [False for i in range(MAX_N)]

# nombre de fois que chaque nom/prénom a été vu jusque maintenant
noms_vus = defaultdict(int)
prenoms_vus = defaultdict(int)

# assurer que nous avons utilisés toutes les passations
passations_utilisees = 0

dieux = {} # nom ---> ID
dieux_nos = [] # ID ---> nom

sys.setrecursionlimit(1000000)
def dfs(i):
    """Faire un dfs pour voir si les règles de passation sont respectées"""
    global passations_utilisees, prenoms_vus, noms_vus, vu
    
    # on a vu ce dieu
    vu[i] = True
    prenoms_vus[dieux_nos[i][0]] += 1
    noms_vus[dieux_nos[i][1]] += 1
    ok = True

    # rendre visite à chaque enfant décrit par une passation
    for j in AL[i]:
        if (not vu[j]):
            passations_utilisees += 1
            ok &= dfs(j)
    
    # un problème plus bas dans l'arbre dfs
    if (not ok):
        return False

    # il y a des dieux auxquels on aurait dû rendre visite en suivant les règles; échec.
    if prenoms_vus[dieux_nos[i][0]] != par_prenom[dieux_nos[i][0]] or noms_vus[dieux_nos[i][1]] != par_nom[dieux_nos[i][1]]:
        ok = False
    return ok

AL = [[] for i in range(MAX_N)]

def gen_AL(passations):
    """Générer le Adjacency List décrite par les passations"""
    for i in range(N):
        for j in range(i):
            # on accepte seulement les passations légales selon les noms des dieux
            if (passations[i][j] or passations[j][i]) and (dieux_nos[i][0] == dieux_nos[j][0] or dieux_nos[i][1] == dieux_nos[j][1]):
                AL[i].append(j)
                AL[j].append(i)

# Lecture de l'entrée
N = int(input())
for i in range(N):
    inp = input()
    pre, nom = inp.split(" ")
    dieux[(pre, nom)] = i
    dieux_nos.append((pre, nom))
    par_nom[nom] += 1
    par_prenom[pre] += 1

M = int(input())
dieux_vus = set([])  # pour vérifier que tous les dieux sont joignables grâce aux passations que nous avons
passations = [[False for i in range(MAX_N)] for j in range(MAX_N)]
for m in range(M):
    pre, nom, pre2, nom2 = input().split(" ")
    d1 = (pre, nom)
    d2 = (pre2, nom2)
    passations[dieux[d1]][dieux[d2]] = True
    dieux_vus.add(dieux[d1])
    dieux_vus.add(dieux[d2])

ans = []
if (len(dieux_nos) == N): # pas tous joignables; échec
    gen_AL(passations)
    for i in range(N): # essayer chaque début
        passations_utilisees = 0
        for j in range(N):
            vu[j] = 0
        noms_vus = defaultdict(int)
        prenoms_vus = defaultdict(int)
        res = dfs(i)
        if (res and (passations_utilisees == M)):
            ans.append(i)

if (len(ans) == 0):
    print("NON")
else:
    print("OUI")
    for i in ans:
        print(f"{dieux_nos[i][0]} {dieux_nos[i][1]}")
