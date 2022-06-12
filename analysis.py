import statistics as s
import matplotlib.pyplot as plt
import sys

files = sys.argv[1:]

costs = []
for fl in files:
    costs.append([])

i = 0
for fl in files:
    with open(fl) as file:
        for line in file:
            ln = line.split(" ")    
            costs[i].append(int(ln[0]))
        i+=1


i = 0
for fl in files:
    print("="*60)
    print(fl)
    print("="*60)
    print("Mean: ", s.mean(costs[i]))
    print("Median: ", s.median(costs[i]))
    print("Variance: ", s.variance(costs[i]))
    print("Min cost: ", min(costs[i]))
    print("Max cost: ", max(costs[i]))
    print("="*60)
    print()
    i+=1


