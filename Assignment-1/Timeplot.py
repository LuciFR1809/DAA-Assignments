import matplotlib.pyplot as plt

X = []
Y = []
with open('autotestcase/time.txt', 'r', encoding='utf8') as f:
    lines = f.readlines()
    for count, time in enumerate(lines):
        X.append(count+1)
        Y.append(int(time))
    plt.plot(X, Y)
    plt.xlabel("No of rectangles")
    plt.ylabel("Time taken in miliseconds")
    plt.savefig('autotestcase/time.png')
    plt.show()
