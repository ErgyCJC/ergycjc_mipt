words = input().split(' ')
frequencies = dict()
for word in words:
    if word in frequencies.keys():
        frequencies[word] += 1
    else:
        frequencies[word] = 1

print(max(frequencies.values()) / len(words))
