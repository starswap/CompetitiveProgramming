import random # may need to try a few times!
import math

# random.seed(10)

def debug_init():
    with open("debug.txt", "w") as f:
        pass

def debug_print(text):
    with open("debug.txt", "a") as f:
        f.write(text)

# debug_init()

def gen_key(length):
    key = ""
    for i in range(length):
        key += random.choice("01")
    return key

LENGTH = 20
ans = -1

for l in range(3, LENGTH):
    number_times = math.ceil(LENGTH / l)
    all_successes = True
    nu_successes = 0

    for n in range(number_times):
        # choose key
        key = gen_key(l)

        # set key 
        for ptr in range(l):
            curr = input()[0]
            if curr != key[ptr]:
                print("? flip")
                input()

        
            print("? left")
   
        # find key
        success = True
        for ptr in range(l):
            curr = input()[0]
            print("? left")
            if curr != key[ptr]:
                success = False
                break

        if not success:
            all_successes = False
            break
        else:
            nu_successes += 1

    if all_successes:
        ans = l
        break

if ans == -1:
    # do something else
    # ans >= LENGTH

    key = gen_key(LENGTH)

    # set key 
    for ptr in range(LENGTH):
        curr = input()[0]
        
        if curr != key[ptr]:
            print("? flip")
            input()
    
        print("? left")

    # find key
    seen = ""
    count = 0
    while True:
        curr = input()[0]
        seen += curr
        if key in seen:
            ans = count + 1
            break

        count += 1 
        print("? left")

print("! " + str(ans))
