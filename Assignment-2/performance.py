import subprocess
from glob import iglob
import matplotlib.pyplot as plt

if __name__ == '__main__':
    outfile = open('performance.txt', 'w', encoding='utf8')
    for i in iglob('autotestcase/*.txt'):
        if i.endswith('_out.txt') or i.endswith('_line.txt'):
            continue

        print(f'Processing {i}')
        fname = i.split('/')[-1]
        result = subprocess.run(['/usr/bin/time', '-v', './main.out',
                                 fname, '1'], stderr=subprocess.PIPE).stderr.decode('utf-8')
        result = result.splitlines()[1:]
        dic = {' '.join(x.split()[:-1])[:-1]: x.split()[-1] for x in result}
        fp = open(i, 'r', encoding='utf8')
        numpoints = len(fp.readlines())
        fp.close()
        memusage = float(dic['Maximum resident set size (kbytes)']) / 1024
        usertime = float(dic['User time (seconds)'])
        systime = float(dic['System time (seconds)'])
        totaltime = usertime + systime
        print('%d %.3f %.3f' % (numpoints, totaltime, memusage), file=outfile)

    outfile.close()

    with open('performance.txt', 'r', encoding='utf8') as perffile:
        lst = []
        for line in perffile.readlines():
            lst.append(list(map(float, line.split())))

        lst.sort()
        numpoints, time, memory = zip(*lst)

        # create figure and axis objects with subplots()
        fig, ax = plt.subplots()
        # make a plot
        ax.plot(numpoints, time, color="red", marker="o")
        # set x-axis label
        ax.set_xlabel("No of points", fontsize=14)
        # set y-axis label
        ax.set_ylabel("Runtime in seconds", color="red", fontsize=14)

        # twin object for two different y-axis on the sample plot
        ax2 = ax.twinx()
        # make a plot with different y-axis using second axis object
        ax2.plot(numpoints, memory, color="blue", marker="o")
        ax2.set_ylabel("Memory usage in Mb", color="blue", fontsize=14)

        fig.savefig('performance.png')
        plt.show()
        