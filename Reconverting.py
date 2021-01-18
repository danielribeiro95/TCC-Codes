with open("Image.jpeg","rb") as image:
    
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

#---------------------------------- CONVERSÃO ----------------------------
            
    for i in range(len(b)):    
        b[i] = int(b[i],2)

    k = bytearray(b)

    image = bytes(k)    #IMAGE = ARQUIVO FINAL

    for i in range(20):
        print(bin_data[i], end = "")

    print("\n")

    for i in range(20):
        print(image[i], end = "")

    file = open("Nova_Imagem.jpeg","wb")
    try:
        file.write(image)
    except:
        print("\nerro")
    finally:
        file.close()
    



        



