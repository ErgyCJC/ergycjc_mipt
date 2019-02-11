def isNotPrime(x):
    for d in range(2, int(x ** 0.5) + 2):
        if x % d == 0:
            return True
    else:
        return False


n = int(input())
result = 2
for i in range(n-1):
    result += 1
    while isNotPrime(result):
        result += 1
print(result)