from random import randint as rnd

h = 56.548542
w = 37.644451
radiation = 8.70

string = f"{h} {w} {radiation} {radiation}"

data_r = open("map/data.txt", "r")
data_text = data_r.read()

data = open("map/data.txt", "w")

data.write(string)

for i in range(100):
    h += rnd(-1000, 1000) / 1000000
    w += rnd(-1000, 1000) / 1000000
    radiation += rnd(-1000, 1000) / 10000

    string = f"{h} {w} {radiation} {radiation}"
    data.write(data_text + "\n" + string)

data.close()