#Testes com biblioteca GPIO
#Default = 5us


import pigpio as gpio
import time

pi = gpio.pi()
pi.set_mode(2,gpio.OUTPUT)

t1 = pi.get_current_tick()
t2 = pi.get_current_tick()

#print((t2-t1)/1000000)
#print(pi.get_mode(2))





