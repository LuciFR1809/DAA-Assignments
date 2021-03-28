import matplotlib.pyplot as plt
import sys
import os
import time
plt.figure(figsize = (5,5))
case=sys.argv[1]
testcase=case+".txt"
print("test case running...do not close window")
with open(testcase, "r") as f:
    s = f.readlines()
    for line in s:
        xleft,ybottom,xright,ytop = list(map(float, line.split()))
        points = [(xleft,ybottom), (xleft,ytop), (xright, ytop), (xright, ybottom), (xleft,ybottom)]
        points = list(zip(*points))
        plt.plot(points[0], points[1], color = 'red')
        plt.savefig(case+".png")
print("test case completed successfully")
time.sleep(1)
os.system("taskkill /f /im cmd.exe")