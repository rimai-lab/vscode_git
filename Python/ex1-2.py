import numpy as np
import matplotlib.pyplot as plt
import csv

x = []

with open('output.csv', 'r') as f:
    r = csv.reader(f)
    for i in r:
        x += [[int(j) for j in i]]
    

head = np.array(x)[:, 0]
resx = np.array(x)[head % 2 == 0, 0]
resy = np.array(x)[head % 2 == 0, 2]

plt.scatter(resx, resy)
plt.savefig("scatter.pdf")