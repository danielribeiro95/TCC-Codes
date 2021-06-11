import serial
import time
import sys

ser = serial.Serial('/dev/ttyS0',9600)
TARGETSIZE = 10

size = ser.read(TARGETSIZE)

size = int(size)

data = ser.read(size)

print(len(data))

ser.close()

fh = open("Received_Image.jpeg","wb")

fh.write(data)
fh.close()


