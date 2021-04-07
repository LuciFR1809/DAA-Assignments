from sys import argv
import numpy as np

if __name__ == '__main__':
    if len(argv) != 4:
        print('Wrong Usage')
        exit(0)
    
    num_points = int(argv[1])
    num_div = int(argv[2])
    filename = argv[3]

    if not (0 < num_div < num_points):
        print('Wrong Usage')
        exit(0)

    fp = open(f'autotestcase/{filename}', 'w', encoding='utf8')

    if num_div == 1:
        m = np.around(np.tan(np.arcsin(np.random.random() * np.random.choice([1, -1]))), 3)
        c = np.around(np.tan(np.arcsin(np.random.random() * np.random.choice([1, -1]))), 3)
        x = 0
        for i in range(num_points):
            print('%.3f %.3f' % (x, m*x + c), file=fp)
            x += (1 - np.around(np.random.random(), 3))

    else:
        points_division = np.random.choice(np.arange(1, num_points-1), num_div-1, replace=False)
        points_division = np.append(points_division, [0, num_points-1])
        points_division.sort()
        point_count = 0
        x = 0
        y = np.around(np.tan(np.arcsin(np.random.random() * np.random.choice([1, -1]))), 3)
        print('%.3f %.3f' % (x, y), file=fp)
        for i in points_division[1:]:
            m = np.around(np.tan(np.arcsin(np.random.random() * np.random.choice([1, -1]))), 3)
            c = y - m*x
            for j in range(point_count+1, i+1):
                x += (1 - np.around(np.random.random(), 3))
                y = m*x + c
                print('%.3f %.3f' % (x, y), file=fp)
                point_count += 1

    fp.close()