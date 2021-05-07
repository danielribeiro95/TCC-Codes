import RPi.GPIO as gpio
from time import sleep

gpio.setmode(gpio.BOARD)
gpio.setup(3,gpio.IN)

while True:
	gpio.wait_for_edge(3,gpio.RISING)
	print("Borda de Subida")
	break

gpio.cleanup()
