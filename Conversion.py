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
    
    #A variável b terá todos os bits da imagem. É uma lista de 152179 str,
#cada string representa um byte.

