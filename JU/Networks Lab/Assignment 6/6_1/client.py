import socket
import time

s = socket.socket()
host = socket.gethostname()
port = 12345

s.connect((host, port))
f = open('tosend.png','rb')
l = f.read(1024)
while (l):
    time.sleep(1)
    print 'Sending...'
    s.send(l)
    l = f.read(1024)
f.close()
print "Done Sending"
s.shutdown(socket.SHUT_WR)
print s.recv(1024)
s.close()
