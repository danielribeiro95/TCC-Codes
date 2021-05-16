#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
//We're gonna use GPIO2 as input

//#define  size 103
//#define size 41319
#define size 51583
#define parity 6

int time_transmission = 10000; // Time in microseconds (for emission)
int k = 0;
void receiving(int gpio, int level, uint32_t tick);
uint32_t start;
uint32_t stop ;
uint32_t time_pulse;
int width;
int old_level;
_Bool file[size+parity];

void reception()
{

	if (gpioInitialise()<0)
	{
		printf("Initialisation Failed \n");
	}

	else
	{
	gpioSetMode(2,0);// 2: Input

	// ------------------------------------ RECEPTION -----------------------------------

	printf("Waiting for signal \n\n");
	while (k < size+parity-1)
	{
	gpioSetAlertFunc(2,receiving);
	}
	// -------------------------------------------- WRITING FILE  ------------------------------------------------

	printf("Received signal (with parity word 010): \n");
	for (int i = 0; i < size+parity; i++){
//	printf("%d",file[i]);
	}

	int final_file[size];


	printf("\n\nReceived Signal (without parity word 010): \n");
	for (int i = 0; i < size; i++){
	final_file[i] = file[i + parity/2];
//	printf("%d",final_file[i]);
	}


	printf("\n\n");

	FILE *file_write;
	file_write = fopen("Received_Text_bin.txt","w");
	for(int i = 0;i<size;i++){
	fputc(final_file[i]+'0',file_write);
	}


	//printf("\n\nEnd of Program\n");
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
