def uint(a):
    return int(a & 0xffffffff)

def byte(a):
    return int(a & 0xff)

class CRC():
    def __init__(self, divisor=0x04C11DB7):
        self.Divisor = divisor
        self.Lut = [None]*256
        self.PopulateCrcLut()

    def PopulateCrcLut(self):
        for i in range(0, 256):
            crc = uint(i << 24)
            for _ in range(0, 8):
                if crc & 0x80000000:
                    crc = uint(uint(crc << 1) ^ self.Divisor)
                else:
                    crc = uint(crc << 1)
            self.Lut[i] = crc

    def GetCrc(self, payload):
        crc_value = uint(0)
        for b in payload:
            pos = byte((crc_value ^ (b << 24)) >> 24)
            crc_value = uint((crc_value << 8) ^ uint(self.Lut[pos]))
        return bytearray(crc_value.to_bytes(4, byteorder="big"))

    def AddCrc(self, payload):
        payload.extend(bytearray(self.GetCrc(payload)))
        return payload

    def VerifyCRC(self, frame):
        return int.from_bytes(self.GetCrc(frame), "big") == 0
