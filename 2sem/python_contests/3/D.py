from collections import defaultdict

line = input()
symbols = defaultdict(int)

for x in line:
    symbols[x] += 1

print(sum(list(symbols.values())) != len(symbols.keys()))
