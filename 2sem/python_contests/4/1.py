def pascal_triangle(count):
    seq = [1]
    while len(seq) <= count:
        print(seq)
        for x in seq:
            yield x
        for index in range(len(seq) - 1, 0, -1):
            seq[index] += seq[index - 1]
        seq = seq + [1]

for x in pascal_triangle(10):
    pass