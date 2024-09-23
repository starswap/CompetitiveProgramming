with open("out2.txt") as f:
    linesA = map(lambda x : x.strip(), f.readlines())

with open("out1.txt") as f:
    linesB = map(lambda x : x.strip(), f.readlines())

for i, (a, b) in enumerate(zip(linesA, linesB)):
    numberA = int(a.split()[-1])
    numberB = int(b.split()[-1])
    if numberA == numberB:
        print(f"Case {i + 1}: Numbers were equal")
    elif numberA <= 2 * numberB and numberB <= 2 * numberA:
        print(f"Case {i + 1}: Binary compatible")
    elif numberA <= 2 * numberB or numberB <= 2 * numberA:
        print(f"Case {i + 1}: Unary compatible")
    else:
        print(f"Case {i + 1}: FAILED")