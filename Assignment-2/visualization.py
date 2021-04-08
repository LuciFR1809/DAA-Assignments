##
 # @file visualization.py
 # @brief Python file for visualization of the testcase.
 # Contains the driver code for reading the file and plotting it.
 # 
 # @authors Kumar Pranjal 2018A7PS0163H
 # @authors Ashna Swaika 2018A7PS0027H
 # @authors Abhishek Bapna 2018A7PS0184H
 # @authors Ashish Verma 2018A7PS0009H

# Importing required modules
from sys import argv
import matplotlib.pyplot as plt
import numpy as np

# Program starts here
if __name__ == '__main__':
    fname = f'autotestcase/{argv[1]}'
    fname2 = f'{fname}_line.txt'
    X = []
    Y = []

    # Plotting the points
    with open(fname, 'r', encoding='utf8') as f:
        lines = f.readlines()
        for line in lines:
            x, y = list(map(float, line.split()))
            X.append(x)
            Y.append(y)
        plt.plot(X, Y, '--.', color='red', linewidth=0.5)

    # Plotting the partitions
    with open(fname2, 'r', encoding='utf8') as f:
        lines = f.readlines()
        err_tot = 0
        for line in lines:
            cost, err, m, c, xmin, xmax = list(map(float, line.split()))
            if m == float('inf'):
                continue
            x = np.linspace(xmin, xmax, 1000)
            plt.plot(x, m*x+c, c=np.random.rand(3,), linewidth=3,
                    label='y = %.3f x + %.3f' % (m, c))
            err_tot += err
        plt.legend()
    # Displaying and saving the plot
    plt.title('Cost : %.3f   Error : %.3f'%(cost,err_tot))
    plt.savefig(f'{fname}.png')
    plt.show()
    exit(0)
