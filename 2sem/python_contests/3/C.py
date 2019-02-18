from collections import Counter

line = input()
size = int(input())

d = Counter()

for x in range(len(line) - size + 1):
    d[line[x:x+size]] += 1

print(sorted([x[0] for x in list(d.items()) if x[1] > 1]))


