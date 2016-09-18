n = int(input())
a = [[1,2,3]]
acopy = [[1,2,3]]
_out = [[1,2]]
del _out[0]
del a[0],acopy[0]
for i in range(n) :
    b = [1,2]
    del b[1],b[0]
    l = list(input())
    for l1 in l :
        b.append(int(l1))
    a.append(b)
    acopy.append(b)
del i
i = 1
while i < n-1 :
    pres = a[i]
    prev = a[i-1]
    nex = a[i+1]
    j = 1
    while j < n-1 :
        if ( pres[j-1]<pres[j]  and pres[j+1]<pres[j] and prev[j]<pres[j] and nex[j]<pres[j] ):
            pres2 = acopy[i]
            pres2[j]=-1
        j += 1
    i += 1
del i
for pres5 in acopy :
    for k in pres5 :
        if k==-1 :
            print('X',end='')
        else :
            print(k,end='')
    print()