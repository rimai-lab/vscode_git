
# coding: utf-8

# In[6]:


import csv

x = []

for i in range(100):
    j = i + 1
    x += [[j, pow(j, 2), pow(j, 3)]]

print(x)
with open('output.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerows(x)

