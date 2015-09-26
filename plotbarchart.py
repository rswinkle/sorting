import numpy as np
import matplotlib.pyplot as plt

lines = open("output.dat").readlines()

#n = [int(x) for x in lines[0].split()[1:]]
n = lines[0].split()[1:]


fig, ax = plt.subplots()

width = 0.15       # the width of the bars
names = []
data = []

for line in lines[1:]:
    l = line.split()
    names += [l[0]]
    data += [[int(x) for x in l[1:]]]



ind = np.arange(len(data[0]))
colors = [ 'c', 'm', 'y', 'r', 'g', 'b' ]

bars = []
for i in range(len(data)):
    print(data[i])
    print(len(ind+width))
    bars += [ax.bar(ind+i*width, data[i], width, color=colors[i])]


ax.set_ylabel("Time in ms (apprx)")
ax.set_title("Quicksort times")
ax.set_xticks(ind+(width*len(names)/2))
ax.set_xticklabels(n)

ax.legend(bars, names, loc=2)


plt.savefig("chart.png")
plt.show()




if False:
    fig, ax = plt.subplots()
    rects1 = ax.bar(ind, menMeans, width, color='r', yerr=menStd)

    womenMeans = (25, 32, 34, 20, 25)
    womenStd =   (3, 5, 2, 3, 3)
    rects2 = ax.bar(ind+width, womenMeans, width, color='y', yerr=womenStd)

    # add some text for labels, title and axes ticks
    ax.set_ylabel('Scores')
    ax.set_title('Scores by group and gender')
    ax.set_xticks(ind+width)
    ax.set_xticklabels( ('G1', 'G2', 'G3', 'G4', 'G5') )

    ax.legend( (rects1[0], rects2[0]), ('Men', 'Women') )

    def autolabel(rects):
        # attach some text labels
        for rect in rects:
            height = rect.get_height()
            ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%d'%int(height),
                    ha='center', va='bottom')

    autolabel(rects1)
    autolabel(rects2)

    plt.show()
