#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
//We're gonna use GPIO2 as input

//#define  size 8
#define size 104

int time_transmission = 1000; // Time in microseconds (for emission)
int k = 0;
void receiving(int gpio, int level, uint32_t tick);
int file[1];
uint32_t start;
uint32_t stop ;
uint32_t time_pulse;
int width;
int old_level;
int parity = 6;

int main()
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
	while (k < size+parity)
	{
	gpioSetAlertFunc(2,receiving);
	}

	// -------------------------------------------- WRITING FILE  ------------------------------------------------

	printf("Received signal (with parity word 010): \n");
	for (int i = 0; i < size+parity; i++){
	printf("%d",file[i]);
	}

	int final_file[size];


	printf("\n\nReceived Signal (without parity word 010): \n");
	for (int i = 0; i < size; i++){
	final_file[i] = file[i + parity/2];
	printf("%d",final_file[i]);
	}




	FILE *file_write;
	file_write = fopen("Received_Text_bin.txt","w");
	for(int i = 0;i<size;i++){
	fputc(final_file[i]+'0',file_write);
	}


	printf("\n\nEnd of Program\n");
	gpioTerminate();
	return 0;
	}
}


void receiving(int gpio, int level, uint32_t tick)
{
	if(k==0){
//		file[k] = level;
		start = tick;
		k++;
		old_level = level;
	}
//	if(k==size+2){
//		file[k]=level;
//		k++;
//	}
	else{
		stop = tick;
		time_pulse = stop - start;
		width = time_pulse/time_transmission;
		if((k==1)&&(width==1)){
			k++;
		}
		if((k==1)&&(width>1)){
			for(int j=0;j< width-1;j++){
				file[k-1] = old_level;
				k++;
			}
		}
		else{
			for (int j = 0; j < width;j++){
				file[k-1] = old_level;
				k++;
			}
		}
		old_level = level;
		start = tick;
	}
}
