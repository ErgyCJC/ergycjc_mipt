def isLucky(x):
    sum1 = sum(list(map(int, list(str(x // 1000)))))
    sum2 = sum(list(map(int, list(str(x % 1000)))))

    return sum1 == sum2 and x > 100000 and x <= 999999

num = int(input())

if num < 100001:
    print(100001)
elif num > 999999:
    print(999999)
else:
    delta = 0
    
    while not isLucky(num + delta) and not isLucky(num - delta):
        delta += 1
    
    if isLucky(num + delta):
        print(num + delta)
    else:
        print(num - delta)
