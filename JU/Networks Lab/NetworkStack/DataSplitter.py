class DataSplitter():
    def SplitData(self, data, size):
        result = []
        for i in range(0, len(data), size):
            result.append(data[i:i+size])
        lendiff = size - len(result[-1])
        if lendiff != 0:
            result2 = bytearray(int(0).to_bytes(lendiff, "big"))
            result2.extend(result[-1])
            result[-1] = result2
        return result
