#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
#include <math.h>
//We're gonna use GPIO21 as input

#define  size 103
//#define size 41319
//#define size 51583

#define GPIO 21


#define parity 6

int time_transmission = 1000; // Time in microseconds (for emission)
int k = 0;
void receiving(int gpio, int level, uint32_t tick);
uint32_t start;
uint32_t stop ;
uint32_t time_pulse;
int width;
int old_level;
_Bool file[size+parity];

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
	while (k < size+parity-1)
	{
	gpioSetAlertFunc(GPIO,receiving);
	}


	// -------------------------------------------- WRITING FILE  ------------------------------------------------


	int final_file[size];


	for (int i = 0; i < size; i++){
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


	printf("\n\nEnd of Program\n");
	gpioTerminate();
	}
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
