# Simulator for C, for testing purposes only
 
import copy
import fractions

p = fractions.Fraction(2, 5)
class Splitter:
    def __init__(self, o1, o2, input_value):
        self.o1 = o1
        self.o2 = o2
        self.input_value = input_value

    def get_o1(self):
        return self.input_value * p

    def get_o2(self):
        return self.input_value * (1 - p)

# spls = [Splitter(-1, 0, 1)]
# spls = [Splitter(-1, 1, 1), Splitter(2, 1, 0),  Splitter(0, -2, 0)]
# spls = [Splitter(-2, 1, 1), Splitter(2, 0, 0),  Splitter(1, -1, 0)]
# spls = [Splitter(1, 2, 1), Splitter(0, -1, 0), Splitter(-2, 0, 0)]

spls = []
N = int(input())
for n in range(N):
    a, b = map(int,input().split())
    spls.append(Splitter(a, b, 0))
spls[0].input_value = 1;

MAX_ITER = 500

outputs = [fractions.Fraction(0,1), fractions.Fraction(0,1)]

for i in range(MAX_ITER):
    new_spls = copy.deepcopy(spls)
    print(f"ITERATION {i + 1}")
    for j in range(len(new_spls)):
        new_spls[j].input_value = 0

    # print(f"Left global output has value {outputs[-1].limit_denominator(max_denominator=7)}")
    # print(f"Right global output has value {outputs[-2].limit_denominator(max_denominator=7)}")

    for j in range(len(spls)):
        # print(f"Splitter {j} has input {spls[j].input_value} first {spls[j].get_o1()} and second {spls[j].get_o2()}")
        if spls[j].o1 in (-1, -2):
            outputs[spls[j].o1] += spls[j].get_o1()
        else:
            new_spls[spls[j].o1].input_value += spls[j].get_o1()
        
        if spls[j].o2 in (-1, -2):
            outputs[spls[j].o2] += spls[j].get_o2()
        else:
            new_spls[spls[j].o2].input_value += spls[j].get_o2()
    
    spls = copy.deepcopy(new_spls)
    print("")
print(f"Left global output has value {float(outputs[-1])}")
print(f"Right global output has value {float(outputs[-2])}")