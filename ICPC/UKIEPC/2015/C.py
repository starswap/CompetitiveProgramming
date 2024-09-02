N = int(input())
lines = sorted([input().split() for i in range(N)])
user_words = {}
for (user, *words) in lines:
    if user not in user_words:
        user_words[user] = []
    for word in words:
        user_words[user].append(word)

word_users = {}
word_uses = {}
for (user, words) in user_words.items():
    for word in words:
        if word not in word_uses:
            word_uses[word] = 1
        else:
            word_uses[word] += 1
        
        if word not in word_users:
            word_users[word] = set([user])
        else:
            word_users[word].add(user)

all_users = filter(lambda word : len(word_users[word]) == len(user_words), word_users)
organised = sorted(all_users, key=lambda word: (-word_uses[word], word))

if len(organised) == 0:
    print("ALL CLEAR")
else:
    print("\n".join(organised))
