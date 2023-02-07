def score(scores):
    reds = [*filter(lambda x : x == 1,scores)]
    colours = [*filter(lambda x : x != 1,scores)]
    
    if (len(colours)) == 0:
        return 1
    else:
        return max(scores) * sum(reds) + sum(reds) + sum(colours)


colourToScore = {"red":1,"yellow":2,"green":3,"brown":4,"blue":5,"pink":6,"black":7}
n = int(input())
scores = []
for i in range(n):
    scores.append(colourToScore[input()])

print(score(scores))

# black
# red
# black
# red
# ---- no more reds
# all others