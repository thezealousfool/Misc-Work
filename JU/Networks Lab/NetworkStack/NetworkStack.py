from NetworkStack import CRC, DataSplitter, IpHandler, MacHandler
from NetworkStack import StopWaitARQ as ARQ

class NetworkStack():
    def __init__(self):
        self.Splitter = DataSplitter.DataSplitter()
        self.IpHandler = IpHandler.IpHandler()
        self.MacHandler = MacHandler.MacHandler()
        self.CRC = CRC.CRC()
        self.ARQ = ARQ.ARQ()
