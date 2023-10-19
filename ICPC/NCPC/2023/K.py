po2 = 4
print(f"buf[{po2 - 1}]")
value = input()
while value != "0":
    po2 *= 2
    print(f"buf[{po2 - 1}]")
    value = input()

# find last index which is non zero
lo = (po2 - 1) // 2 # in
hi = (po2 - 1) # out
while hi - lo != 1:
    mi = (hi + lo) // 2
    print(f"buf[{mi}]")
    value = input()
    if value == "0":
        hi = mi
    else:
        lo = mi
print(f"strlen(buf) = {lo + 1}")