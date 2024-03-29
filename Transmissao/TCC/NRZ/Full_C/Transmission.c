#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <pigpio.h>
#include <math.h>

#define GPIO 20

int resto;
int potencia;

int time_transmission = 1000;
int parity = 6;

uint32_t time1;
uint32_t time2;
int time3;

int main(){

if (gpioInitialise()<0){
printf("Initialisation Failed \n");
}

else{

// -------------------------------- CONVERSION ----------------------------


	time1 = gpioTick();

	FILE *file_read;
	file_read = fopen("Doc1.txt","r");

    	fseek(file_read,0,SEEK_END);  //Get the size of the file
	int size = ftell(file_read); // Ignore the last element (end of file)
	printf("\nSize = %d \n", size);
	rewind(file_read);

	int val[size];
	_Bool bin[size][8];

    for (int i = 0; i < size ; i++){
        val[i] = (int)fgetc(file_read); 
//        printf("%d ",val[i]);
    }

    fclose(file_read);
    printf("\n\n");


    for (int i = 0; i < size; i++){
        for(int j = 0; j < 8; j++){
            if(j ==0)
                {bin[i][j] = val[i]/128; resto = val[i]%128;}
            else{
                potencia = pow(2,7-j);
                bin[i][j] = resto/(potencia);
                resto = resto%potencia;
            }
//            printf("%d",bin[i][j]);
        }
//        printf("  ");
    }


	_Bool header[3] = {0, 1, 0};

	time2 = gpioTick();

	time3 = (time2-time1);

	printf("\n\nProcessing time = %d microseconds", time3);

// ---------------------------------- TRANSMISSION ------------------


	gpioSetMode(GPIO,1);

	gpioDelay(2000000);

	time1 = gpioTick();

	for(int i = 0; i < parity/2;i++){
	gpioWrite(GPIO,header[i]);
	gpioDelay(time_transmission);
	}

	for(int i = 0;i<size;i++){
        	for (int j = 0; j<8;j++){
		gpioWrite(GPIO,bin[i][j]);
		gpioDelay(time_transmission);
        	}
	}

	for(int i = 0; i<parity/2;i++){
	gpioWrite(GPIO,header[i]);
	gpioDelay(time_transmission);
	}

	
	time2 = gpioTick();

	time3 = (time2-time1);

	printf("\n\nTransmission time = %d microseconds ", time3);

	gpioTerminate();


printf("\n");


}
}
