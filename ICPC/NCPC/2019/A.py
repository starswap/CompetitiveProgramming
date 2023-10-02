last = input()
N = int(input())
words = [input() for i in range(N)]
target_start = last[-1]
can = None
for word in words:
    if word[0] == target_start:
        can = word
        break
if not can:
    print("?")
else:
    first_letters_count = {}
    for word in words:
        if word[0] in first_letters_count:
            first_letters_count[word[0]] += 1
        else:
            first_letters_count[word[0]] = 1
    
    done = False
    for sugg in words:
        if (sugg[-1] not in first_letters_count or first_letters_count[sugg[-1]] == 1 and sugg[0] == sugg[-1]) and sugg[0] == target_start:
            print(sugg + "!")
            done = True
            break
    if not done:
        print(can)

