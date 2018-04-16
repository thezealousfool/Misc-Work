from NetworkStack.NetworkStack import NetworkStack
from TransmissionMedium import TransmissionMedium

class Device():
    def __init__(self, Ip, Mac):
        self.NetworkStack = NetworkStack()
        self.Ip = Ip
        self.Mac = Mac
        self.TransmissionMedium = TransmissionMedium()
        self.TransmissionMedium.AddTerminal(self)

    def GetTransmissionMedium(self):
        return self.TransmissionMedium

    def SendData(self, frame):
        medium = self.TransmissionMedium
        medium.AddFrame(frame, medium.Device1 == self)
        self.NetworkStack.ARQ.Transmit(medium, medium.Device1 == self)

    def ReceiveData(self, frame):
        
        self.TransmissionMedium.Transmit()

    def CheckFrameMac(self, frame):
        _, dest, source, payload = self.NetworkStack.MacHandler.ExtractMacFromFrame(frame)
        if dest == self.Mac:
            return True, dest, source, payload
        else:
            return False, dest, source, payload

    def CheckFrameIp(self, packet):
        dest, source, payload = self.NetworkStack.IpHandler.ExtractIpFromFrame(packet)
        if dest == self.Ip:
            return True, dest, source, payload
        else:
            return False, dest, source, payload
