import serial
from datetime import datetime

ser = serial.Serial('/dev/ttyACM0',9600)

i = 0

while i < 100:
	out = ser.readline().rstrip();
	out = str(datetime.now()) + " " + out
	print (out)
	i = i+1 
