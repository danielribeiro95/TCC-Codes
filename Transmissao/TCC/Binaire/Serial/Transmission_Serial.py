import time
import serial
import sys

ser = serial.Serial('/dev/ttyS0',2400)

img = "/home/pi/GitHub/TCC-Codes/Transmissao/TCC/Binaire/Serial/image.jpeg"
TARGETSIZE = 10

file = open(img,"rb")
data = bytearray(file.read())
print(str(len(data))+" bytes\n")

size = str(len(data))

size = size.zfill(TARGETSIZE)

size = bytes(size,'ascii')

ser.write(size)
ser.flush()

ser.write(data)
#print(data)

ser.close()
