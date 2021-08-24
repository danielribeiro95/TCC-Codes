import serial
import time
import sys

ser = serial.Serial('/dev/ttyS0',2400)
TARGETSIZE = 10

size = ser.read(TARGETSIZE)

time1 = time.time()

size = int(size)

data = ser.read(size)

print(str(len(data)) + " bytes \n")

ser.close()

print("Transmission time = %s seconds\n" %(time.time()-time1))

time1 = time.time()

fh = open("Received_Image.jpeg","wb")

fh.write(data)
fh.close()

print("Writing time = %s seconds" %(time.time()-time1))



