import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)
gpio.setup(3,gpio.OUT)

preambulo = [1,0,1,0,1,0,1,0,1,0]
tempo = 0.1



with open("Doc1.txt","rb") as doc:
	bin_data = doc.read()

	dado = []
	for i in range(len(bin_data)):
		dado.append(bin(bin_data[i]))
	dado_final = []
	for i in range(len(dado)):
		a = dado[i].replace('0','',1)
		b = a.replace('b','')
		dado_final.append(b)
	for i in range(len(dado_final)):
		while len(dado_final[i])<8:
			dado_final[i] = '0' + dado_final[i]

	#for i in range(len(dado_final)):
	#	for m in range(len(dado_final[0])):
	#		print(dado_final[i][m],end='')
	#	print("  ")

	print("Tipo de dado: " + str(type(dado_final)))
	print("Tipo de dado de cada elemento da lista: " + str(type(dado_final[0])))
	print("Primeiro elemento da lista: " + str(dado_final[0]))
	print("Tipo de dado de cada bit dos 'bytes' da lista: " + str(type(dado_final[0][0])))
	print("Primeiro elemento do primeiro 'byte' da lista: " + str(dado_final[0][0]))
	print("Tamanho do Arquivo: " + str(len(dado_final)))
	
	dado_final_2 = ''.join(dado_final)
	print("\n" + dado_final_2)
	file_write = open("Doc1_bin.txt","w")
	file_write.write(dado_final_2)
	file_write.close()

while True:
	break
	for i in range(len(preambulo)):
		gpio.output(3,preambulo[i])
		time.sleep(tempo)

	for i in range(len(dado_final)):
		for m in range(len(dado_final[i])):
			gpio.output(3,int(dado_final[i][m]))
			time.sleep(tempo)


	print("Fim")
	break

gpio.cleanup()
