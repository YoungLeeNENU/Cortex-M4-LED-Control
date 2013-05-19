# -*- coding:utf-8 -*-
## LED CONTROL CLIENT USING TCP CONNECTION
import re
import sys
import time
from socket import *

pattern = re.compile(r"q$|quit$", re.IGNORECASE)
## BOARD'S DEFAULT IP ADDRESS IS 192.168.0.10 AND HERE WE USE PORT 8000
default = {"HOST": "192.168.0.10", "PORT": 8000}
auto_msg = [1, 2, 3, 4]    ## FOR AUTO LED RUN

case = raw_input("USE DEFAULT? (y/n)> ")
if case in ["N", "n"]:
	HOST = raw_input("HOST> ")
	PORT = raw_input("PORT> ")
elif case in ["Y", "y"]:
	HOST = default["HOST"]
	PORT = default["PORT"]
BUFSIZE = 1024
ADDR = (str(HOST), int(PORT))

client = socket(AF_INET, SOCK_STREAM)    ## SET SOCK_STREAM FOR TCP CONNECTION
client.connect(ADDR)

def msg_auto():
	for x in range(10):
		for y in auto_msg:
			if client.send(str(y)):
				print "MESSAGE " + str(4 * x + y) + " SENT!"
				time.sleep(0.5)

while 1:
	data = raw_input("INPUT> ")
	if not data:
		break
	elif data in ["auto", "AUTO"]:
		msg_auto()
		continue
	if client.send(data):
		print "MESSAGE SENT!"
	if re.match(pattern, data, 0) != None:
		sys.exit()

client.close()
