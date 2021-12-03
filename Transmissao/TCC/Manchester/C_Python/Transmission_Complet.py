import ctypes

print("File Conversion")

with open("bee_movie.txt","rb") as doc:
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



	dado_final_2 = ''.join(dado_final)
	#print("\n" + dado_final_2)
	file_write = open("Doc1_bin.txt","w")
	file_write.write(dado_final_2)
	file_write.close()


print("\nEnd of Conversion\n")

print("\nTransmission:")

transmission = ctypes.CDLL("/home/pi/GitHub/TCC-Codes/Transmissao/TCC/Manchester/C/Transmission.so")

transmission.transmission()

print("\nEnd of Transmission")

