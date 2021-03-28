from sys import argv
import matplotlib.pyplot as plt
import sys
import os
import time
import matplotlib.pyplot as plt
case=sys.argv[1]
testcase=case+".txt"
print("test case running...do not close window")
with open(testcase, 'r', encoding='utf8') as f:
    lines = f.readlines()
    for line in lines:
        x_left, y_bottom, x_right, y_top = list(map(float, line.split()))
        bottom_left = (x_left, y_bottom)
        top_left = (x_left, y_top)
        top_right = (x_right, y_top)
        bottom_right = (x_right, y_bottom)
        x, y = zip(bottom_left, top_left, top_right, bottom_right, bottom_left)
        plt.plot(x, y, color='red')

with open(case+'_out.txt', 'r', encoding='utf8') as f:
    lines = f.readlines()

    for line in lines:
        if line == '' or line =='\n':
            continue

        if line.startswith('Measure'):
            plt.title(line)
            continue
            
        x_left, y_bottom, x_right, y_top = list(map(float, line.split()))
        bottom_left = (x_left, y_bottom)
        top_left = (x_left, y_top)
        top_right = (x_right, y_top)
        bottom_right = (x_right, y_bottom)
        x, y = zip(bottom_left, top_left, top_right, bottom_right, bottom_left)
        plt.plot(x, y, color='green')

plt.savefig(testcase+'vis.png')
print("test case completed successfully")
time.sleep(1)
os.system("taskkill /f /im cmd.exe")
