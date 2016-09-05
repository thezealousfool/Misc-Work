T = int(input())
a1 = [[1,2],[3,4]]
del a1[1],a1[0]
for i in range(T) :
    n = int(input())
    a = int(input())
    b = int(input())
    temp = [1,2]
    del temp[1], temp[0]
    for x in range(n) :
        y = n-1-x
        temp.append(x*a + y*b)
    del x
    temp.sort()
    a1.append(temp)
del i
for i in a1 :
    for x in i :
        print(x,end=' ')
    print()
