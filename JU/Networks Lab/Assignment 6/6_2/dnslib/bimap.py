
class Bimap(object):

    """
    A simple bi-directional map which returns either forward or
    reverse lookup of key.
    """

    def __init__(self,forward):
        self.forward = forward
        self.reverse = dict([(v,k) for (k,v) in forward.items()])

    def lookup(self,k,default=None):
        try:
            try:
                return self.forward[k]
            except KeyError:
                return self.reverse[k]
        except KeyError:
            if default:
                return default
            else:
                raise
    
    def __getitem__(self,k):
        return self.lookup(k,k)

    def __getattr__(self,k):
        return self.lookup(k,k)

if __name__ == '__main__':
    import doctest
    doctest.testmod()
