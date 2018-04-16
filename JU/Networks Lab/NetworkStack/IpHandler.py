class IpHandler():
    def AddIp(self, packets, sourceIp, destinationIp):
        result = []
        for packet in packets:
            result.append(self.AddIpToPacket(packet, sourceIp, destinationIp))
        return result

    def AddIpToPacket(self, packet, sourceIp, destinationIp):
        sourceSplit = sourceIp.split('.')
        destinationSplit = destinationIp.split('.')
        result = bytearray()
        for byte in destinationSplit:
            result.append(int(byte, 10))
        for byte in sourceSplit:
            result.append(int(byte, 10))
        result.extend(packet)
        return result

    def ExtractIpFromFrame(self, frame):
        destination = frame[0:4]
        source = frame[4:8]
        payload = frame[8:]
        destinationStr = ''
        for byte in destination:
            destinationStr = destinationStr + repr(byte) + '.'
        destinationStr = destinationStr[:-1]
        sourceStr = ''
        for byte in source:
            sourceStr = sourceStr + repr(byte) + '.'
        sourceStr = sourceStr[:-1]
        return (
            destinationStr,
            sourceStr,
            payload
        )
