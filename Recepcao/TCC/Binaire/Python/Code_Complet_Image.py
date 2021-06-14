import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)
gpio.setup(3,gpio.IN)

arquivo = []
amostragem = 10
bytes_arquivo = 152179
bits = bytes_arquivo*8 + 10
tempo = 0.1/amostragem
decisao = 7



while True:

	gpio.wait_for_edge(3,gpio.RISING)
	start = time.time()

	for i in range(bits*amostragem - 500):
        	arquivo.append(gpio.input(3))
        	time.sleep(tempo)

	end1 = time.time()
	print("Tempo de Leitura: " + str(end1-start) + " Segundos")

	file = []
	count = 0
	for i in range(len(arquivo)):
		if (i==0):
			a = arquivo[0]
		else:
			if (arquivo[i]==a):
				count = count+1
				if  (i==len(arquivo)-1):
					quociente  = count//amostragem
					if (count%10 >= 7):
						quociente=quociente +1
						for i in range(quociente):
							file.append(a)
					else:
						for i in range(quociente):
							file.append(a)
			else:
				quociente = count//amostragem
				if (count%amostragem >= 7):
					for i in range(quociente+1):
						file.append(a)
					count = 0
					a = arquivo[i]
				else:
					for i in range(quociente):
						file.append(a)
					count = 0
					a = arquivo[i]
	
	#print(type(file))
	#print(len(file))
	#print(type(file[0]))


	for i in range(5):
		file.remove(1)
		file.remove(0)
	

	#for i in range(len(file)):
	#	print(file[i],end='')
	#	if (i%7 == 0)and(i!=0):
	#		print(" ")
	

	h = ""
	data = []
	count = 0

	for i in range(len(file)):
		h = h +str(file[i])
		count = count +1
		if (count == 8):
			data.append(h)
			h = ""
			count = 0


	for i in range(len(data)):
		data[i] = int(data[i],2)

	k = bytearray(data)

	text = bytes(k)

	file = open("Received_Image.jpeg","wb")
	try:
		file.write(text)
	except:
		print("\nerro")
	finally:
		file.close()


	

	end2 = time.time()

	print("Tempo de Conversão: " + str(end2-end1) + " Segundos")

	print("FIM")

	print("Tempo Total: " + str(end2 - start) + " Segundos")

	break

gpio.cleanup()
