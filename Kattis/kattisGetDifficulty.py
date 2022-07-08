import bs4
import requests

lo = 0
hi = 33

f = open(r'''C:\users\marks\Documents\CP Problems\Kattis\Difficulties.txt''',"w",encoding="utf-8")

for i in range(lo,hi+1):
        soup = bs4.BeautifulSoup(requests.get("https://open.kattis.com/problems?page=" + str(i)).text)
        pageProbs = soup.findAll("tr")[1:]#.parent.parent.findChildren()[6]

        for prob in pageProbs:
                f.write(prob.findChildren()[0].findChildren()[0].contents[0] + "," + prob.findChildren()[6].findChildren()[0].contents[0] + '\n')

f.close()
