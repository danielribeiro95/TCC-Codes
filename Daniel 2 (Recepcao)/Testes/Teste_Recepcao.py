import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)

gpio.setup(3, gpio.IN)

while True:
	x = gpio.input(3)
	print(x)
	time.sleep(0.25)



gpio.cleanup()
