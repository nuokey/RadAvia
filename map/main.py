import folium

data = open("map/data.txt").read();

data = data.split("\n")
for i in range(len(data)):
    data[i] = data[i].split()
    for q in range(len(data[i])):
        data[i][q] = float(data[i][q])

print(data)

m = folium.Map(location=[data[0][0], data[0][1]], zoom_start=16)

for dot in data:
    color = "purple";
    if dot[2] <= 10:
        color="green";
    elif dot[2] >= 10 and dot[2] <= 20:
        color="yellow";
    elif dot[2] >= 20:
        color="red";
    # elif dot[2]
    folium.Circle(radius=100, location=[dot[0], dot[1]], color=color, popup=dot[2], fill=True).add_to(m)

m.save('name.html')