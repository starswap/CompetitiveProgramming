def get_adverts(songs, start_point):
    i = start_point

    ads = 0
    last_ad = 0
    while not i == (start_point - 1) % N:
        last_ad += songs[i]
        if last_ad >= C:
            ads += 1
            last_ad = 0
        i += 1
        i %= N

    return ads

N, C = map(int,input().split())
songs = list(map(int, input().split()))
adverts = []
for i in range(N):
    ads = get_adverts(songs, i)
    adverts.append(ads)


print(" ".join(map(str, adverts)))
