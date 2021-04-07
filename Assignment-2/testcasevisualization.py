from sys import argv
import matplotlib.pyplot as plt

if __name__ == '__main__':
    if len(argv) != 2:
        print('Wrong Usage')
        exit(0)

    filename = argv[1]
    lst = []
    with open(f'autotestcase/{filename}', 'r', encoding='utf8') as fp:
        for line in fp.readlines():
            lst.append(list(map(float, line.split())))

    lst.sort()
    x, y = zip(*lst)
    plt.plot(x, y, 'r.-')
    plt.show()