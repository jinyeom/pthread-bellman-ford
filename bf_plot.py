import re
import subprocess
import numpy as np
from matplotlib import pyplot as plt

def plot_nthreads_time(prog, filename, src, title, show=False, save=False):
    # plot the naive pthread implemenation of computation of pi with 1, 2, 4, 8 threads
    print("Plotting runtimes of {} with 1, 2, 4, 8 threads...".format(prog))
    speedups = []

    result = subprocess.run([prog, "-f", filename, "-s", src], stdout=subprocess.PIPE).stdout.decode("utf-8")
    serial_runtime = float(re.search(r"elapsed process CPU time = (.*) nanoseconds", result).group(1))

    for n in [1, 2, 4, 8]:
        print("Running {} with {} thread(s)...".format(prog, n), flush=True, end="")
        result = subprocess.run([prog, ], stdout=subprocess.PIPE).stdout.decode("utf-8")
        print("\x1B[32mdone\x1B[0m")
        # first line of the result should have the runtime
        parallel_runtime = float(re.search(r"elapsed process CPU time = (.*) nanoseconds", result).group(1))
        speedups.append(serial_runtime / parallel_runtime)

    plt.figure()
    plt.title(title)
    plt.xlabel("number of threads")
    plt.ylabel("speedup")
    plt.plot(n_threads, speedups, marker="o")
    if show:
        print("Displaying the plot...")
        plt.show()
    if save:
        print("Saving plot figure...", flush=True, end="")
        plt.savefig("{}.png".format(title))
        print("\x1B[32mdone\x1B[0m")
        plt.close()

plot_nthreads_time("./bellman-ford", "/tmp/jinyeom/rmat15.dimacs", , save=True)
