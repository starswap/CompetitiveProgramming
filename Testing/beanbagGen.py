import random
import subprocess

B_MIN = 20
B_MAX = 20
T_MIN = 100
T_MAX = 100

random.seed(100)
TCs = 100
for tc in range(TCs):
    output = ""
    B = random.randint(B_MIN,B_MAX)
    T = random.randint(T_MIN,T_MAX)


    output += str(B) + "\n"
    amts = []
    for b in range(B):
        amts.append(random.randint(0,100))
    output += " ".join(map(str,amts)) + "\n"

    output += str(T) + "\n"
    for t in range(T):
        amt = random.randint(0,B)
        output += str(amt) + " "
        poss = list(range(1,B+1))
        random.shuffle(poss)
        output += " ".join(map(str,poss[:amt]))
        output += "\n"

    print(f"TC {tc}")
    # pythonOut = str(subprocess.run("python Kattis/beanbagPython.py",capture_output=True,text=True,input=output).stdout)
    with open(r"..\Kattis\a.in","w") as f:
        f.write(output)
    # cPPOut = str(subprocess.run("./Kattis/a.exe",capture_output=True,text=True,input=output).stdout)
    # if pythonOut != cPPOut:
        # print("Python Output: " + pythonOut)
    # print("CPP Output: " + cPPOut)
    # print("Input: " + output)
