import matplotlib.pyplot as plt

with open("04.txt", "r") as f:
    n = int(f.readline())
    x = []
    y = []
    for line in f:
        x.append(int(line.split()[0]))
        y.append(int(line.split()[1]))

plt.plot(x, y, color='green', marker='o', markersize=7)
plt.show()
