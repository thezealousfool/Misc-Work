from Device import Device

class WorkStation(Device):
    def __init__(self, Ip, Mac):
        super(WorkStation, self).__init__(Ip, Mac)

    def CheckFrameMac(self, frame):
        proceed, _, _, packet = super().CheckFrameMac(frame)
        if proceed:
            self.CheckFrameIp(packet)
        else:
            print(self.Ip, "Ignoring frame::Frame not for me")

    def CheckFrameIp(self, packet, frame=None):
        proceed, _, sourceIp, payload = super().CheckFrameIp(packet)
        if proceed:
            print(self.Ip, "Proceeding to read packet")
        else:
            print(self.Ip, "Ignoring packet::Packet not for me")
