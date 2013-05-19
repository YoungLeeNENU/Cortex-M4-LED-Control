# -*- coding:utf-8 -*-
## LED CONTROL CLIENT USING UDP CONNECTION
import re
import sys
import time
from socket import *

pattern = re.compile(r"q$|quit$", re.IGNORECASE)
## BOARD'S DEFAULT IP ADDRESS IS 192.168.0.10 AND HERE WE USE PORT 8000
default = {"HOST": "192.168.0.10", "PORT": 8000}
auto_msg = [1, 2, 3, 4]    ## FOR AUTO LED RUN

case = raw_input("USE DEFAULT HOST(192.168.0.10) AND PORT(8000)? (y/n)> ")
if case in ["N", "n"]:
	HOST = raw_input("HOST> ")
	PORT = raw_input("PORT> ")
elif case in ["Y", "y"]:
	HOST = default["HOST"]
	PORT = default["PORT"]
BUFSIZ = 1024
ADDR = (str(HOST), int(PORT))

client = socket(AF_INET, SOCK_DGRAM)    ## SET SOCK_DGRAM FOR UDP CONNECTION

def msg_auto():
	for x in range(10):
		for y in auto_msg:
			if client.sendto(str(y), ADDR):
				print "MESSAGE " + str(4 * x + y) + " SENT!"
				time.sleep(0.5)

def msg_send():
	while 1:
		data = raw_input("INPUT> ")
		if data in ["auto", "AUTO"]:
			msg_auto()
			continue
		try:
			if int(data) not in [1, 2, 3, 4]:
				print "LED NUMBER IN RANGE [1, 2, 3, 4], TRY AGAIN!"
				continue
			elif client.sendto(data, ADDR):
				print "MESSAGE SENT!"
		except:
			if re.match(pattern, data, 0) != None:
				sys.exit()
			else:
				print "INPUT FORMAT ERROR! TRY AGAIN!"
				msg_send()
				break

print "==========================================="
print "INPUT THE LED ID NUMBER TO TRUN ON THE LED,\n \
AUTO TO ACTIVATE AUTO MODE,\n \
Q TO EXIT."
print "==========================================="

msg_send()

client.close()
