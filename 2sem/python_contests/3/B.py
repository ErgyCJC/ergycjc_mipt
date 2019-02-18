line1 = input()
line2 = input()

result = dict(zip(line1, line2))

if len(line1) > len(line2):
    for x in range(len(line1)-len(line2)):
        result[line1[len(line2) + x]] = None

print(sorted(result.items()))


