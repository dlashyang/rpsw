#!/usr/bin/env python

import socket

class cmsp_client(object):
    def __init__(self, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.addr = ('127.0.0.1', port)
        self.sock.connect(self.addr)

    def request(self, msg):
        self.sock.send(msg)
        reply = self.sock.recv(1000)
        print('Reply is %s' % reply)

if __name__ == '__main__':
    while 1:
        cli = cmsp_client(9911)
        print('input msg:')
        send_msg = raw_input()
        if (send_msg == 'exit'):
            break;
        cli.request(str(send_msg))

