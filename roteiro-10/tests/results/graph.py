import numpy as np
import matplotlib.pyplot as plt
import sys

x1 = []
x2 = []
y = []

with open (sys.argv[1], 'r') as f:
    for line in f:
        cols = line.strip("\n").split(" ")
        if cols[0].isnumeric():
            y.append(int(cols[0]))
        elif cols[0] == 'Comparations':
            x1.append(int(cols[2]))
        elif cols[0] == 'Swaps':
            x2.append(int(cols[2]))

print(x1, x2, y)

plt.plot(x1, y, 'o', markersize=2, label='Tempo decorrido')
# plt.plot(x2, y, 'o', markersize=2, label='Tempo decorrido')

# p = np.polyfit(x1, y, 2)
# plt.plot(x1, np.ployval(p, x1), 'red', linewidth=2, label='Regressão polinomial')

plt.xlabel('Quantidade de elementos')
plt.ylabel('Tempo de execução (s)')
plt.title('Algoritmo')

plt.legend()
plt.show()