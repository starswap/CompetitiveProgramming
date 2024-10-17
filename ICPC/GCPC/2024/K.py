from collections import Counter
message = input()
instructions = input()

h = Counter(instructions)["h"] % 2
r = Counter(instructions)["r"] % 2
v = Counter(instructions)["v"] % 2

def do_h(s):
    dic = {"p": "q", "b" : "d", "d": "b", "q": "p"}
    y = [dic[c] for c in reversed(s)]
    return "".join(y)

def do_v(s):
    dic = {"p": "b", "q" : "d", "d": "q", "b": "p"}
    y = [dic[c] for c in s]
    return "".join(y)

def do_r(s):
    dic = {"q": "b", "p" : "d", "b": "q", "d": "p"}
    y = [dic[c] for c in reversed(s)]
    return "".join(y)

if h:
    message = do_h(message)
if r:
    message = do_r(message)
if v:
    message = do_v(message)
print(message)