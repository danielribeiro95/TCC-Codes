# TCC-Codes
Created Codes for a direct VLC 

Precisamos de dois códigos (para duas RaspBerry Pi) em Python:

1: Emissão
Para a emissão, utilizaremos uma figura (nomeada "figure.jpeg"). Iremos carregá-la na primeira raspberry e transformá-la em uma sequência de Bits. Enviaremos tais bits para o GPIO, resultando na emissão pela luz.

2: Recepção
Iremos utilisar interrupção para o início da recepção. Um sinal de sincronização deve ser utilizado antes do dado.
Devemos criar um código para reestruturar a imagem.


Os códigos do projeto possuem as seguintes funções:

-jpeg_bin_conversion: Converte a imagem em uma sequência de bits

-Reconverting: Reconverte a sequência de bits em uma imagem
