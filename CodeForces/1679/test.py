import random
with open("output.txt","w") as f:
    f.write("173070 169783 989451008964122129\n")
    weights = []
    for i in range(173070):
        weights.append(random.randint(1,100000))
    f.write(" ".join(map(str,weights)) + "\n")
    
    for j in range(169783):
        
        a = random.randint(1,173070)
        b = a
        while b == a:
            b = random.randint(1,173070)
        
        f.write(f"{a} {b}\n")

