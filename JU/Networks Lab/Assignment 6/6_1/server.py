import socket

s = socket.socket()
host = socket.gethostname()
port = 12345
s.bind((host, port))
f = open('torecv.png','wb')
s.listen(5)
while True:
    c, addr = s.accept()
    print 'Got connection from', addr
    l = c.recv(1024)
    print "Receiving..."
    while (l):
        f.write(l)
        l = c.recv(1024)
        print "Receiving..."
    f.close()
    print "Done Receiving"
    c.send('Server :: Thank you')
    c.close()
    break

