N = int(input())
l = []
m = []
for i in range(N):
    inp = input().split()
    l += inp
for w in l:
    word = list(w)
    for letr in word:
        if not('a'<=letr<='z' or 'A'<=letr<='Z'):
            word.remove(letr)
    k = (''.join(word)).lower()
    m.append(k)
m.sort()
del w
for wo1 in m:
    print(wo1)
exit(1)
