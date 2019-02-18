from collections import defaultdict

line = input()
symbols = defaultdict(int)

for x in line:
    symbols[x] += 1

if sum(list(symbols.values())) == len(symbols.keys()):
    print(False)
else:
    print(True)


