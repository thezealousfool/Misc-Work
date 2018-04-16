from Router import Router
from WorkStation import WorkStation

if __name__ == '__main__':
    r = Router('192.168.0.0', 'AA:AA:AA:AA:AA:AA')
    pc1 = WorkStation('192.168.0.1', 'AB:AB:AB:AB:AB:AB')
    pc2 = WorkStation('192.168.0.2', 'AC:AC:AC:AC:AC:AC')
    payload = bytearray('Hello World', 'utf-8')
    frame = pc1.NetworkStack.MacHandler.AddMacToFrame(
        payload, 'ab:ab:ab:ab:ab:ab', 'aa:aa:aa:aa:aa:aa', 1)
    r.CheckFrameMac(frame)
