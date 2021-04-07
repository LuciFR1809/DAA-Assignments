from sys import argv
import matplotlib.pyplot as plt
import numpy as np
fname2 = f'testcases/{argv[1]}'+'_line.txt'
fname = f'testcases/{argv[1]}'
X = []
Y = []
with open(fname, 'r', encoding='utf8') as f:
    lines = f.readlines()
    for line in lines:
        x, y = list(map(float, line.split()))
        X.append(x)
        Y.append(y)
    #plt.scatter(X, Y, color='red')
    plt.plot(X, Y, '-o', color='red', linewidth=0.5)
x = np.linspace(0, 15, 1000)
with open(fname2, 'r', encoding='utf8') as f:
    lines = f.readlines()
    err_tot = 0
    for line in lines:
        err, m, c, xmin, xmax = list(map(float, line.split()))
        x = np.linspace(xmin, xmax, 1000)
        plt.plot(x, m*x+c, c=np.random.rand(3,), linewidth=3,
                 label="y = "+str(m)+"*x + "+str(c))
        err_tot = err_tot+err
    plt.plot(0, 0, linewidth=0, label="error = "+str(err_tot))
    plt.legend()
plt.savefig(f'{fname}.png')
plt.show()
exit()
