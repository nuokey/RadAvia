import folium

data = open("map/data.txt").read();
max_rad = 0;
min_rad = 100000;

data = data.split("\n")
for i in range(len(data)):
    data[i] = data[i].split()
    for q in range(len(data[i])):
        data[i][q] = float(data[i][q])
    
    if data[i][2] > max_rad:
        max_rad = data[i][2]

    if data[i][2] < min_rad:
        min_rad = data[i][2]



m = folium.Map(location=[data[0][0], data[0][1]], zoom_start=16)

amplitude = max_rad - min_rad

border1 = min_rad + amplitude * 1 / 3

border2 = min_rad + amplitude * 2 / 3

for dot in data:
    if dot[2] <= border1:
        color="green";
    elif dot[2] >= border1 and dot[2] <= border2:
        color="yellow";
    elif dot[2] >= border2:
        color="red";

    folium.Circle(radius=5, location=[dot[0], dot[1]], color=color, popup=dot[2], fill=True).add_to(m)

m.save('name.html')

print("Минимальное значение радиационного фона", min_rad)
print("Первая граница: ", border1)
print("Вторая граница: ", border2)
print("Максимальное значение радиационного фона", max_rad)