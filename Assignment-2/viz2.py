from sys import argv
import matplotlib.pyplot as plt
import numpy as np
fname2 = f'testcases/{argv[1]}'+'_line.txt'
M = []
c = []
x = np.linspace(0, 10, 1000)
with open(fname2, 'r', encoding='utf8') as f:
    lines = f.readlines()
    for line in lines:
        m, c = list(map(float, line.split()))
        plt.plot(x, m*x+c, '--r')
        print(m, ' ', c)
plt.savefig(f'{fname2}brrrr.png')
plt.show()
