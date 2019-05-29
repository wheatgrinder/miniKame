import socket

s = socket.socket()
s.connect(("192.168.1.31", 8888))
s.send("W")
s.close()
