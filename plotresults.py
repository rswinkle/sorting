import numpy as np
import matplotlib.pyplot as plt


lines = open("output.dat").readlines()

n = [int(x) for x in lines[0].split()[1:]]

names = []
for line in lines[1:]:
    l = line.split()
    names += [l[0]]
    d = [int(x) for x in l[1:]]
    plt.plot(n, d)

plt.show()

