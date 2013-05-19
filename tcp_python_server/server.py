# -*- coding:utf-8 -*-
## LED CONTROL SERVER USING TCP CONNECTION
import re
import sys
import time
import random
from socket import *

pattern = re.compile(r"q$|quit$", re.IGNORECASE)
## SERVER'S DEFAULT IP ADDRESS IS 192.168.0.11 AND HERE WE USE PORT 8000
default = {"HOST": "192.168.0.11", "PORT": 8000}

case = raw_input("USE DEFAULT? (y/n)> ")
if case in ["N", "n"]:
	HOST = raw_input("HOST> ")
	PORT = raw_input("PORT> ")
elif case in ["Y", "y"]:
	HOST = default["HOST"]
	PORT = default["PORT"]
BUFSIZE = 1024
ADDR = (str(HOST), int(PORT))

server = socket(AF_INET, SOCK_STREAM)    ## SET SOCK_STREAM FOR TCP CONNECTION
server.bind(ADDR)
server.listen(5)

while 1:
	print 'WAITING FOR CONNECTION...'
	client, addr = server.accept()
	print "GET CONNECTION FROM:", addr

	while 1:
		data = client.recv(BUFSIZE)
		print data
		if not data:
			break
		else:
			led_num = random.choice(['1', '2', '3', '4', "auto"])
		client.send(led_num)
		print led_num + " WAS SENT JUST NOW."
		if re.match(pattern, data, 0) != None:
			sys.exit()

client.close()

server.close()
