#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
//We're gonna use GPIO21 as input

//#define  size 103 // Hello World
#define size 51583 // Bee Movie

#define parity 1

#define GPIO 21
#define time_half_bit 500

int k = 0;
void receiving(int gpio, int level, uint32_t tick);
uint32_t stop ;
uint32_t time_limit = time_half_bit + time_half_bit/2;
int j = 0;
int old_level;
_Bool file[size];

void reception()
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
	while (k < 2*(size+parity)-1)
	{
	gpioSetAlertFunc(GPIO,receiving);
	}
	// -------------------------------------------- WRITING FILE  ------------------------------------------------



	printf("\n\n");

	FILE *file_write;
	file_write = fopen("Received_Text_bin.txt","w");
	for(int i = 0;i<size;i++){
	fputc(file[i]+'0',file_write);
	}


	gpioTerminate();
	}
}


void receiving(int gpio, int level, uint32_t tick)
{
	switch (k){
	case 0:
	break;
	case 1:
	break;
	default:
		if((tick - stop)>(time_limit)){
		k++;
		file[j] = old_level;
		j++;
		}
		else{
		if(k%2 == 0){
		file[j] = level;
		j++;
		}
		}

	}

	stop = tick;
	k++;
	old_level = level;
}
