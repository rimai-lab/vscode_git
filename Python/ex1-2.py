import csv

x = []

with open('output.csv', 'r') as f:
    r = csv.reader(f)
    x = [i for i in r]

l = []
for j in x if j[0] % 2 == 0:
    l += [j[0], j[2]]

print(l)
