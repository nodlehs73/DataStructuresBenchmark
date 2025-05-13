import random
import subprocess
import matplotlib.pyplot as plt
import matplotlib
import matplotlib.ticker as ticker

font = {'family': 'georgia'}
matplotlib.rc('font', **font)

def create_test (n, want, sequential):

    file_name = get_test_name(n, want, sequential)
    sequence = [i for i in range (n)]

    if not sequential:
        random.shuffle (sequence)

    with open (file_name, "w") as w_file:
        w_file.write (f"{n if want[0] else n * 2} ")

        w_file.write (" ".join (map (lambda x: "0 " + str(x) , sequence)))
        w_file.write (" ")
        if want[1] and want[2]:
            if not sequential:
                random.shuffle (sequence)

            sliced_seq = sequence[:n // 2]
            w_file.write (" ".join (map (lambda x: "2 " + str (x), sliced_seq)))
            w_file.write(" ")
            w_file.write (" ".join (map (lambda x: "1 " + str (x), sliced_seq)))

        elif want[1]:

            if not sequential:
               random.shuffle (sequence)

            w_file.write (" ".join (map (lambda x: "1 " + str (x), sequence)))
        elif want[2]:
            if not sequential:
                random.shuffle (sequence)

            w_file.write (" ".join (map (lambda x: "2 " + str (x), sequence)))

def get_test_name (n, want, sequential):
    ops = ["i", "d", "s"]
    want_ops = [op for i, op in enumerate(ops) if want[i]]
    file_name = f"{"sequential" if sequential else "random"}_test{n}{"".join(want_ops)}.txt"

    return file_name, want_ops

cpp = ["splay", "skiplist", "tango"]
sizes = [2 ** i for i in range (14, 25)]

names = ["Insert Only Benchmark"]
for title_name, want_want in zip (names, [[1, 0, 0]]):
    for want_sequential in [False]:
        time = {}
        if not want_want[1]:
            time = {"splay" : [], "skiplist" : [], "tango" : []}
        else:
            time = {"splay" : [], "skiplist" : []}

        markers = ['x', '^', 'o']

        for cpp_file in cpp:
            if cpp_file == "tango" and want_want[1]:
                continue

            for i in range (14, 25):
                want_n = 2 ** i
                file_name, want_ops = get_test_name (want_n, want_want, want_sequential)

                with open (file_name, "r") as read_file:

                    result = subprocess.run ([f"./{cpp_file}", *want_ops], stdin = read_file, capture_output=True)

                    print (file_name)

                    result = result.stdout.decode ()

                    time[cpp_file].append (float (result))
                    print (result)


        plt.figure (dpi = 600)

        for (name, times), marker_ in zip (time.items(), markers):
            plt.plot (sizes, times, label = name, marker = marker_)


        plt.xscale('log', base = 2)
        plt.yscale ('log', base = 10)
        plt.gca().yaxis.set_major_formatter(ticker.ScalarFormatter())
        plt.xlabel("Input size (log2 scale)")
        plt.ylabel("Time (ms)")
        plt.title(("Sequential " if want_sequential else "Random ") + title_name)
        plt.legend(time.keys())
        plt.show ()


#only insert 10, 100, 10000, 100000000 operations
#insert some numbers and then search (sequential and then random)
#insert and then delete all numbers (sequential and then random)
# 50% insert 25% search and then 25% delete random (random)
