from threading import Thread

class ARQ():
    def __init__(self):
        self.ackReceived = True
    
    def Transmit(self, medium, forward=True):
        ack = self._transmit(medium, forward)
    
    def _transmit(self, medium, forward):
        transmitted = medium.Transmit(forward, 1)
        acks = [None]*len(transmitted)
        
