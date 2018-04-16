
import types
from bit import get_bits,set_bits
from buffer import Buffer

class DNSLabelError(Exception):
    pass

class DNSLabel(object):

    def __init__(self,label):
        """
            Create label instance from elements in list/tuple. If label
            argument is a string split into components (separated by '.')
        """
        if type(label) in (types.ListType,types.TupleType):
            self.label = tuple(label)
        else:
            self.label = tuple(label.split("."))

    def __str__(self):
        return ".".join(self.label)

    def __repr__(self):
        return "%r" % ".".join(self.label)

    def __hash__(self):
        return hash(self.label)

    def __eq__(self,other):
        return self.label == other.label

    def __len__(self):
        return len(".".join(self.label))

class DNSBuffer(Buffer):

    def __init__(self,data=""):
        """
            Add 'names' dict to cache stored labels
        """
        super(DNSBuffer,self).__init__(data)
        self.names = {}

    def decode_name(self):
        """
            Decode label at current offset in buffer (following pointers
            to cached elements where necessary)
        """
        label = []
        done = False
        while not done:
            (len,) = self.unpack("!B")
            if get_bits(len,6,2) == 3:
                # Pointer
                self.offset -= 1
                pointer = get_bits(self.unpack("!H")[0],0,14)
                save = self.offset
                self.offset = pointer
                label.extend(self.decode_name().label)
                self.offset = save
                done = True
            else:
                if len > 0:
                    label.append(self.get(len))
                else:
                    done = True
        return DNSLabel(label)

    def encode_name(self,name):
        """
            Encode label and store at end of buffer (compressing
            cached elements where needed) and store elements
            in 'names' dict
        """
        if not isinstance(name,DNSLabel):
            name = DNSLabel(name)
        if len(name) > 253:
            raise DNSLabelError("Domain label too long: %r" % name)
        name = list(name.label)
        while name:
            if self.names.has_key(tuple(name)):
                # Cached - set pointer
                pointer = self.names[tuple(name)]
                pointer = set_bits(pointer,3,14,2)
                self.pack("!H",pointer)
                return
            else:
                self.names[tuple(name)] = self.offset
                element = name.pop(0)
                if len(element) > 63:
                    raise DNSLabelError("Label component too long: %r" % element)
                self.pack("!B",len(element))
                self.append(element)
        self.append("\x00")

if __name__ == '__main__':
    import doctest
    doctest.testmod()
