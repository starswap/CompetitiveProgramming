from collections import OrderedDict

subs = OrderedDict({"at":"@","and":"&","one":"1","won":"1","too":"2","two":"2","to":"2","four":"4","for":"4",
        "bea":"b","bee":"b","be":"b","sea":"c","see":"c","eye":"i","owe":"o","oh":"o","are":"r","you":"u","why":"y"})

lines = int(input())
for i in range(lines):
        line = input()
        j = 0
        while j != len(line) -1:
                for sub in subs:
                        if line[j:j+len(sub)] == sub:
                                line = line[:j] + "$"+subs[sub]+"$" + line[j+len(sub):]
                        elif line[j:j+len(sub)] == sub[0].upper()+sub[1:]:
                                line = line[:j] + "$"+subs[sub][0].upper()+subs[sub][1:]+"$" + line[j+len(sub):]
                j = j+1
        print(line.replace("$",""))


