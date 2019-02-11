line = input().split()
n = int(line[0])
m = int(line[1])
result = [[i*x for i in range(1, m+1)] for x in range(1, n+1)]
print('\n'.join([' '.join([str(x) for x in row]) for row in result]))