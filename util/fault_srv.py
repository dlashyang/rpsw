#!/usr/bin/env python

import sys
import time
import socket
import select
import threading

class name_server(object):
    def __init__(self,port=9003,buf_len=2048):
        print("server init.")
        self.addr=('127.0.0.1', port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.buf_len=buf_len
        self.interval=3
        self.stop = 0

    def run(self):
        self.thrd_echo=threading.Thread(target = self.echo, args = (), name = 'echo')
        self.thrd_echo.start()

    def echo(self):
        print('server start.')

        self.sock.bind(self.addr)
        while True:
            if self.stop:
                print ('server stop.')
                break

            (r,w,e)=select.select([self.sock],[],[],self.interval)

            if self.sock in r:
                (data,addr) = self.sock.recvfrom(self.buf_len)
                print ('msg from (%s:%s): %s' %(addr[0],addr[1],data))

    def close(self):
        self.stop = 1
        self.thrd_echo.join()
        self.sock.close()
        print("server close.")

if __name__ == '__main__':
    port = 19993
    serv=name_server(port)
    print("server is running on %d" % port)
    try:
        serv.run()
        data=raw_input()
        serv.close()
    except:
        serv.close()