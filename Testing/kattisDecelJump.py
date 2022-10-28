with open("input.txt","w") as f:
    inp = [-1000000000 for i in range(3000)]
    f.write(
        "3000\n"+ 
        ' '.join(map(str,inp))
    )

