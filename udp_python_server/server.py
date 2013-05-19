# -*- coding:utf-8 -*-
## LED CONTROL SERVER USING UDP CONNECTION
import re
import sys
from socket import *

pattern = re.compile(r"q$|quit$", re.IGNORECASE)
## SERVER'S DEFAULT IP ADDRESS IS 192.168.0.11 AND HERE WE USE PORT 8000
default = {"HOST": "192.168.0.11", "PORT": 8000}

case = raw_input("USE DEFAULT HOST(192.168.0.11) AND PORT(8000)? (y/n)> ")
if case in ["N", "n"]:
	HOST = raw_input("HOST> ")
	PORT = raw_input("PORT> ")
elif case in ["Y", "y"]:
	HOST = default["HOST"]
	PORT = default["PORT"]
BUFSIZ = 1024
ADDR = (str(HOST), int(PORT))

server = socket(AF_INET, SOCK_DGRAM)    ## SET SOCK_DGRAM FOR UDP CONNECTION
server.bind(ADDR)

def msg_send():
	while 1:
		data, ADDR = server.recvfrom(BUFSIZ)
		print data
		data = raw_input("INPUT> ")
		if re.match(pattern, data, 0) != None:
			sys.exit()
		try:
			server.sendto(data, ADDR)
			msg_show()
		except:
			print "ERROR, CONNECT AGAIN!"
			msg_send()
			break

def msg_show():
	print "========================================================="
	print "PRESS KEY 1 ON THE BOARD TO SEND A REQUEST TO THE SERVER.\n \
	INPUT THE LED ID NUMBER TO TRUN ON THE LED,\n \
	AUTO TO ACTIVATE AUTO MODE,\n \
	Q TO EXIT."
	print "========================================================="

msg_show()
msg_send()

server.close()
