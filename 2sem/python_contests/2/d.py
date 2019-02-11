n = int(input())
a = 0
db = 1
if n == 0:
    print(a)
else:
    for x in range(n):
        a, b = b, a+b
    print(a)
