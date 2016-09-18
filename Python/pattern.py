T = int(input())
_r = [1,2]
del _r[1], _r[0]
for T1 in range(T):
    _input = [['1','2']]
    del _input[0]
    inp_i = input()
    inp_i1 = inp_i.split()
    hi = int(inp_i1[0])
    wi = int(inp_i1[1])
    for i in range(hi):
        temp = ['1','2']
        del temp[1], temp[0]
        temp = list(input())
        _input.append(temp)
    _pattern = [['1','2']]
    del _pattern[0]
    inp_i = input()
    inp_i1 = inp_i.split()
    hp = int(inp_i1[0])
    wp = int(inp_i1[1])
    for i in range(hp):
        temp = ['1','2']
        del temp[1], temp[0]
        temp = list(input())
        _pattern.append(temp)
    i = 0
    k = _pattern[0][0]
    while i <= hi-hp :
        j = 0
        while j <= wi-wp :
            if (_input[i][j] == k):
                
            j += 1
        i += 1