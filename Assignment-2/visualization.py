from sys import argv
import matplotlib.pyplot as plt

fname = f'testcases/{argv[1]}'
X = []
Y = []
with open(fname, 'r', encoding='utf8') as f:
    lines = f.readlines()
    for line in lines:
        x, y = list(map(float, line.split()))
        X.append(x)
        Y.append(y)
    
    plt.scatter(X, Y, color='red')

plt.savefig(f'{fname}_out.png')
plt.show()