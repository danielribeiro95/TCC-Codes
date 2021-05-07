# -*- coding: utf-8 -*-

import RPi.GPIO as gpio
import time



gpio.setmode(gpio.BOARD)
gpio.setup(3, gpio.OUT)

gpio.output(3, 0)

preambulo = [0,1,0,1,0,1,0,1,0]

tempo = 0.1

with open("/home/pi/Documents/TCC/image.jpeg" , "rb") as image:
	bin_data = image.read()

	real_bin = []
	for i in range(len(bin_data)):
		real_bin.append(bin(bin_data[i]))

	b = []
	for i in range(len(real_bin)):
		a = real_bin[i].replace('0','',1)
		c = a.replace('b','')
		b.append(c)

	for i in range(len(b)):
		while len(b[i])<8:
			b[i] = "0" + b[i]

	print("Tamanho do arquivo " + str(len(b)))

# A variável b terá todos os bits da imagem (lista de 152179 str, cada um com 8 bits).


while True:
    
    gpio.output(3,1)
    
    start_time = time.time()
    
    for i in range(len(preambulo)):
        time.sleep(tempo)
        gpio.output(3, preambulo[i])
        
        
    
    for i in range(len(b)):
        for m in range(len(b[i])):
                time.sleep(tempo)
                gpio.output(3,int(b[i][m]))
            
            
    print("---- %s seconds ----" %(time.time() - start_time))

    gpio.output(3,0)
    print("Fim")
    break

gpio.cleanup()
