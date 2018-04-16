class MacHandler():
    def AddMac(self, frames, source, destination):
        result = []
        frameNo = 0
        for frame in frames:
            result.append(self.AddMacToFrame(frame, source, destination, frameNo))
            frameNo = frameNo + 1
        return result
    
    def AddMacToFrame(self, frame, source, destination, id):
        sourceSplit = source.split(':')
        destinationSplit = destination.split(':')
        result = bytearray(id)
        for byte in destinationSplit:
            result.append(int(byte,16))
        for byte in sourceSplit:
            result.append(int(byte, 16))
        result.extend(frame)
        return result

    def ExtractMacFromFrame(self, frame):
        id = frame[0]
        destination = frame[1:6]
        source = frame[6:12]
        payload = frame[12:]
        destinationStr = ''
        for byte in destination:
            destinationStr = destinationStr + hex(byte)[2:] + ':'
        destinationStr = destinationStr[:-1]
        sourceStr = ''
        for byte in source:
            sourceStr = sourceStr + hex(byte)[2:] + ':'
        sourceStr = sourceStr[:-1]
        return (
            id,
            destinationStr,
            sourceStr,
            payload
        )
