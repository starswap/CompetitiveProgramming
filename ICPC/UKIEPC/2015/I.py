hard = ["b", "c", "d", "g", "k", "n", "p", "t", "B", "C", "D", "G", "K", "N", "P", "T"]
endings = ["ah", "oh", "uh"]

def dist(str1, str2):
    return abs(ord(str1[0]) - ord(str2[0]))

def replace_hard(word, bestc):
    res = []
    for char in word:
        if char in hard:
            res.append(bestc)
        else:
            res.append(char)
    return "".join(res)

def select_best(lst, compto):
    best = 10000000
    bestc = "a"
    for char in lst:
        if dist(char, compto) < best:
            best = dist(char, compto)
            bestc = char
    return bestc

def solve_word(word):
    bestc = select_best(hard, word[0])
    word = bestc + word[1:]

    syllables = word.split("-")
    syllables[1:] = map(lambda s : replace_hard(s, bestc.lower()),  syllables[1:])
    word = "".join(syllables)

    if word[-1] in hard:
        bestend = select_best(endings, word[-1].lower())
        word += bestend
    return word

words = input().split(" ")
print(" ".join(map(solve_word, words)))
