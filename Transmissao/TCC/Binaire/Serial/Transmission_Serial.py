import time
import serial
import sys

ser = serial.Serial('/dev/ttyS0',9600)

img = "/home/pi/GitHub/TCC-Codes/Transmissao/TCC/Serial/image.jpeg"
TARGETSIZE = 10

file = open(img,"rb")
data = bytearray(file.read())
print(len(data))

size = str(len(data))

size = size.zfill(TARGETSIZE)

size = bytes(size,'ascii')

ser.write(size)
ser.flush()

ser.write(data)
#print(data)

ser.close()
