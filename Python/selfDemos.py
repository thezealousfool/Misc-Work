def sum(a,b):
        return a+b

class ABC :
    def subs(self,a,b):
        return a-b

obj = ABC()
print(sum(12,25))
print(obj.subs(25,12))
