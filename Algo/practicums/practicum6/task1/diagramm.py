import matplotlib.pyplot as plt

# Чтение данных из файла
data = []
with open("hash_collisions.txt", "r") as file:
    for line in file:
        hash_value, collisions = line.strip().split()
        data.append((int(hash_value), int(collisions)))

# Сортировка данных по хэш-значению
data.sort(key=lambda x: x[0])

# Извлечение хэш-значений и количества коллизий в отдельные списки
hash_values = [entry[0] for entry in data]
collision_counts = [entry[1] for entry in data]

# Построение столбчатой диаграммы
plt.bar(hash_values, collision_counts)
plt.xlabel("Hash Value")
plt.ylabel("Collision Count")
plt.title("Hash Function Collisions")
plt.savefig("bar_chart.png")
plt.show()
