import serial
import time

ser = serial.Serial("/dev/ttyUSB1", baudrate=115200, timeout=3.0)
#ser = serial.Serial("/dev/ttyUSB2", 115200, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
#print(ser.name)
#ser.write("s 0 0 255 255 0")

while True:
	print ser.readline()
	for x in range(0,10):
		for y in range(0,7):
			ser = serial.Serial("/dev/ttyUSB1", baudrate=115200, timeout=3.0)
			cmd = "s " + str(x) + " " + str(y)  + " 255 255 255 "
			print cmd
			ser.write(""+cmd)
			time.sleep(1)
			ser.close()
	
	#ser.write("s 0 2 255 255 255 ")
	time.sleep(2)
	ser.close()
