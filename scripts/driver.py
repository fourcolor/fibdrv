#!/usr/bin/env python3

import subprocess
import numpy as np
import matplotlib.pyplot as plt

runs = 100


def outlier_filter(datas, threshold=2):
    datas = np.array(datas)
    z = np.abs((datas - datas.mean()) / datas.std())
    return datas[z < threshold]


def data_processing(data_set, n):
    catgories = data_set[0].shape[0]
    samples = data_set[0].shape[1]
    final = np.zeros((catgories, samples))

    for c in range(catgories):
        for s in range(samples):
            final[c][s] =                                                    \
                outlier_filter([data_set[i][c][s] for i in range(n)]).mean()
    return final


mode = {
    0: "fib_sequence_str", 3: "fib_sequence_bn", 4: "fib_sequence_bn_fast_double"
}
color = {
    0: "red", 3: "blue", 4: "green"
}

if __name__ == "__main__":
    fig, ax = plt.subplots(1, 1, sharey=True)
    for j in mode.keys():
        Ys = []
        for i in range(runs):
            comp_proc = subprocess.run(
                'sudo ./client '+str(j)+'> /dev/null', shell=True)
            output = np.loadtxt('data', dtype='float').T
            Ys.append(np.delete(output, 0, 0))
        X = output[0]
        Y = data_processing(Ys, runs)


        ax.plot(X, Y[0], markersize=1,
                label=mode[j], color=color[j])
    ax.set_title('perf', fontsize=16)
    ax.set_xlabel(r'$n_{th}$ fibonacci', fontsize=16)
    ax.set_ylabel('time (ns)', fontsize=16)
    ax.legend(loc='lower right')

    plt.savefig("statistic.png")
