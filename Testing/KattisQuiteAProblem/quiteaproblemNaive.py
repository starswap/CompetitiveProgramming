try:
    while True:
        line = input().lower()
        print("yes" if "problem" in line else "no")

except EOFError:
    pass