from Device import Device

class Router(Device):
    def __init__(self, Ip, Mac):
        super(Router, self).__init__(Ip, Mac)
        self.IpMap = {}
        self.PortMap = {}
        self.AvailablePorts = [
            1,2,3,4,5
        ]
        self.AvailablePorts.reverse()
        self.TransmissionMediumMap = {}
        for p in self.AvailablePorts:
            self.PortMap[p] = None
            self.TransmissionMediumMap[p] = None

    def ConnectDevice(self, d):
        port = self.AvailablePorts.pop()
        self.PortMap[port] = d
        self.IpMap[d.Ip] = port
        d.TransmissionMedium.AddTerminal(self)
        self.TransmissionMediumMap[port] = d.TransmissionMedium

    def CheckFrameMac(self, frame):
        proceed, _, _, packet = super().CheckFrameMac(frame)
        if proceed:
            self.CheckFrameIp(packet, frame)
        else:
            print(self.Ip, "Ignoring frame::Frame not for me")

    def CheckFrameIp(self, packet, frame=None):
        proceed, destIp, sourceIp, payload = super().CheckFrameIp(packet)
        if proceed:
            print(self.Ip, "Proceeding to read packet")
        else:
            if destIp in self.IpMap:
                port = self.IpMap[destIp]
                medium = self.TransmissionMediumMap[port]
                medium.AddFrame(frame)
                medium.Transmit(medium.Device1 == self, 1)
            else:
                print(self.Ip, "Ignoring packet::Packet not for any device connected to this router")
