totalOK = 0
totalFail = 0

dx = [0,1,-1,0]
dy = [1,0,0,-1]

with open("output.txt") as f:
  lines = list(map(lambda a : a.strip(), f.readlines()))
  i = 0
  while i < len(lines):
    if "Case" in lines[i]:
      if "Impossible" in lines[i]:
        totalOK += 1
        pass
      elif "Possible" in lines[i]:
        current = []
        i += 1
        while i < len(lines) and not("Case" in lines[i]):
          current.append(lines[i])
          i += 1

        ok = True
        for r in range(len(current)):
          for c in range(len(current[r])):
            if (current[r][c] == '^'):
              total = 0
              for j in range(4):
                if (r+dy[j] >= 0 and r+dy[j] < len(current) and c+dx[j] >= 0 and c+dx[j] < len(current[r]) and current[r+dy[j]][c+dx[j]] == '^'):
                  total += 1

              if total < 2:
                ok = False
                
        if ok:
          totalOK += 1
        else:
          totalFail += 1
        continue
    i += 1
print(f"{totalOK} OKs and {totalFail} fails.")
    
        
    
        
