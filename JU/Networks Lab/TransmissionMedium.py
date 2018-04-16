import time

class TransmissionMedium():
    def __init__(self, delay=.1):
        self.Device1 = None
        self.Device2 = None
        self.delay = delay
        self.d1SendBuffer = []
        self.d1ReceiveBuffer = []
        self.d2SendBuffer = []
        self.d2ReceiveBuffer = []
        self.ack = True

    def AddTerminal(self, d):
        if self.Device1 == None:
            self.Device1 = d
        elif self.Device2 == None:
            self.Device2 = d
        else:
            return False
        return True

    def AddFrame(self, frame, forward=True):
        if forward:
            self.d1SendBuffer.append(frame)
        else:
            self.d2SendBuffer.append(frame)

    def Transmit(self, forward=True, noFrames=-1):
        transmitted = []
        time.sleep(self.delay * 2)
        if forward:
            if noFrames < 0:
                noFrames = len(self.d1SendBuffer)
            for _ in range(0, noFrames):
                time.sleep(self.delay)
                data = self.d1SendBuffer.pop()
                transmitted.append(data)
                self.Device2.ReceiveData(data)
        else:
            if noFrames < 0:
                noFrames = len(self.d2SendBuffer)
            for _ in range(0, noFrames):
                time.sleep(self.delay)
                data = self.d2SendBuffer.pop()
                transmitted.append(data)
                self.Device1.ReceiveData(data)
        return transmitted
