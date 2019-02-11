n = int(input())
for x in range(1, n+1):
    if x != 1:
        print(', ', end='')
    if x % 15 == 0:
        print('Fizz Buzz', end='')
    elif x % 3 == 0:
        print('Fizz', end='')
    elif x % 5 == 0:
        print('Buzz', end='')
    else:
        print(x, end='')

