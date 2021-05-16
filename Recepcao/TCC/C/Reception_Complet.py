import ctypes


print("Reception\n")

reception = ctypes.CDLL("/home/pi/GitHub/TCC-Codes/Recepcao/TCC/C/Reception.so")

reception.reception()

print("End of Reception")

print("\n\nReconversion")

with open("Received_Text_bin.txt","r") as doc:
	data = doc.read()

	h = ""
	file = []
	count = 0

	for i in range(len(data)):
		h = h +str(data[i])
		count = count+1
		if(count == 8):
			file.append(h)
			h = ""
			count =0

	for i in range(len(file)):
		file[i] = int(file[i],2)

	k = bytearray(file)

	final_file = bytes(k)

	file_write = open("Received_Image.jpeg","wb")
	try:
		file_write.write(final_file)
	except:
		print("\nError")
	finally:
		file_write.close()

	print("\nEnd of Reconversion")
