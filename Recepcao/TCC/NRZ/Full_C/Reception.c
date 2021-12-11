#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
#include <math.h>
//We're gonna use GPIO21 as input

#define  size 13 // hello world
//#define size 6448 //bee movie

#define GPIO 20

#define parity 6

int time_transmission = 1000; // Time in microseconds (for emission)
int k = 0;
void receiving(int gpio, int level, uint32_t tick);
uint32_t start;
uint32_t stop ;
uint32_t time_pulse;
int width;
int old_level;
_Bool file[8*size+parity];

int main()
{

	if (gpioInitialise()<0)
	{
		printf("Initialisation Failed \n");
	}

	else
	{
	gpioSetMode(GPIO,0);// 2: Input

	// ------------------------------------ RECEPTION -----------------------------------

	printf("Waiting for signal \n\n");
	while (k < (8*size)+parity-1)
	{
	gpioSetAlertFunc(GPIO,receiving);
	}


	// -------------------------------------------- WRITING FILE  ------------------------------------------------

	int size2 = sizeof(file)/(sizeof(file[0]));
	printf("Size of received bits = %d \n",size2);



	_Bool final_file[8*size];

	for (int i = 0; i < 8*size; i++){
	final_file[i] = file[i + parity/2];
	}


	printf("\n\n");


	int val[size];

	FILE *file_write;
	file_write = fopen("Received_Text.txt","w");

    	for (int i = 0; i < size; i++){
        val[i] = 0;
        for(int j = 0; j < 8; j++){
            val[i] =val[i]+ final_file[j + i*8]*pow(2,7-j);
        }
        fputc((char)val[i],file_write);
	}

	fclose(file_write);


	gpioTerminate();
	}



	// ---------------------------------- BER ----------------------------------

	FILE *file_read;
	FILE *file_original;
	file_read = fopen("Received_Text.txt","r");
	file_original = fopen("Doc1.txt","r");

	fseek(file_read,0,SEEK_END);  //Get the size of the file
	int size = ftell(file_read); // Ignore the last element (end of file)
	printf("\nSize = %d \n", size);
	rewind(file_read);


	int val[size];
	_Bool bin[size][8];
	int original_file[size];
	_Bool original_file_bin[size][8];


    for (int i = 0; i < size ; i++){
        val[i] = (int)fgetc(file_read);
		original_file[i] = (int)fgetc(file_original); 
		// printf("%d ",original_file[i]);
        // printf("%d ",val[i]);
    }

    fclose(file_read);
	fclose(file_original);

    printf("\n\n");


    for (int i = 0; i < size; i++){
        for(int j = 0; j < 8; j++){
            if(j ==0){
				bin[i][j] = val[i]/128; 
				original_file_bin[i][j] = original_file[i]/128;
				resto = val[i]%128;
				resto_original = original_file[i]%128;
				}
            else{
                potencia = pow(2,7-j);
                bin[i][j] = resto/(potencia);
				original_file_bin[i][j] = resto_original/(potencia);
                resto = resto%potencia;
				resto_original = resto_original%potencia;
            }
           printf("%d",bin[i][j]);
		   if(bin[i][j] != original_file_bin[i][j])
		   		BER_bit++;
        }
       printf("  ");
    }

	printf("\n \n");

	for (int i = 0; i < size; i++){
		for (int j = 0; j < 8; j++){
			printf("%d",original_file_bin[i][j]);
		}
		printf("  ");
	}

	printf("\n\n");
	BER = (double)BER_bit/(double)size;

	printf("BER = %d/%d = %f \n",BER_bit, size, BER);

 
	printf("\n");


	printf("\n\nEnd of Program\n");




}


void receiving(int gpio, int level, uint32_t tick)
{
	switch (k){
	case 0:
		file[k] = 0;
		k++;
	break;
	case 1:
		stop = tick;
		file[k] = old_level;
		k++;
	break;
	default:
		stop = tick;
		time_pulse = stop - start;
		width = time_pulse/time_transmission;
		for (int j = 0; j < width;j++){
			file[k] = old_level;
			k++;
		}
	}
	old_level = level;
	start = tick;
}
