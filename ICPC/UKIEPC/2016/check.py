import subprocess

def is_ok(ops, target):
    if len(ops) > 40:
        return False
    else:
        reg = {"A" : 1000, "X": 1000, "Y": 1000}
        stack = []
        for op in ops:
            code, *operands = op.split()
            if code == "AD":
                a = stack.pop()
                b = stack.pop()
                stack.append((a + b) & ((1 << 8) - 1))
            elif code == "PH":
                stack.append(reg[operands[0]])
            elif code == "PL":
                reg[operands[0]] = stack.pop()
            elif code == "ZE":
                reg[operands[0]] = 0
            elif code == "ST":
                reg[operands[0]] = 1
            elif code == "DI":
                return reg[operands[0]] == target

import time

for i in range(256):
    start = time.time()
    result = subprocess.check_output(["python", "luke.py"], input=bytes(str(i), "ascii"))
    end = time.time()
    ops = result.decode("ascii").strip().split("\n")
    print(f"{i} {is_ok(ops, i)} - {end - start} - {len(ops)}")