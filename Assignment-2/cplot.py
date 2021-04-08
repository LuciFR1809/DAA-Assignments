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
    fname = f'{argv[1]}'
    X = []
    Y = []
    Z = []
    # Plotting the points
    with open(fname, 'r', encoding='utf8') as f:
        lines = f.readlines()
        for line in lines:
            x, y, z = list(map(float, line.split()))
            X.append(x)
            Y.append(y)
            Z.append(z)
        plt.plot(X, Y, '-', color='blue', linewidth=1,label='error')
        plt.plot(X, Z, '--', color='green', linewidth=0.5,label='no. of partitions')
    plt.legend()
    # Displaying and saving the plot
    plt.savefig(f'{fname}.png')
    plt.show()
    exit(0)
