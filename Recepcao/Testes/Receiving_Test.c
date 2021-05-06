#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
//We're gonna use GPIO2 as input

#define  size 6

int sampling = 10;
int decision = 6;
int time_transmission = 10000; // Time in microseconds (for emission)
int k = 0;
void receiving(int gpio, int level, uint32_t tick);
int file[1];

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
	while (k == 0)
	{
	gpioSetAlertFunc(2,receiving);
	}

	// -------------------------------------------- WRITING FILE  ------------------------------------------------

	printf("Received signal before processing: \n");
	for (int i = 0; i < sampling*size; i++){
	printf("%d",file[i]);
	}

	int final_file[size];
	int count = 0;
	int a = file[0];
	int quocient;
	int k = 0;

	for (int i = 0; i < sampling*size; i++){
	if (i==0){
	a = file[0];}
	else{
		if(file[i] == a){
			count = count+1;
			if (i == (size*sampling)-1){
				quocient = count/sampling;
				if (count%sampling >= decision){
					for(int j = 0; j < quocient+1; j++){
						final_file[k] = a;
						k++;
					}
				}
				else{
					for(int j = 0; j < quocient; j++){
						final_file[k] = a;
						k++;
					}
				}
			}
		}
		else{
			quocient = count/sampling;
			if(count%sampling >= decision){
				for(int j = 0; j< quocient+1;j++){
					final_file[k] = a;
					k++;
				}
				count = 0;
				a = file[i];
			}
			else{
				for(int j = 0; j<quocient;j++){
					final_file[k] = a;
					k++;
				}
				count = 0;
				a = file[i];
			}
		}
	}
	}

	printf("\n\nSignal After Processing: \n");
	for (int i = 0; i < size ; i++){
	printf("%d",final_file[i]);
	}

	printf("\n\nEnd of Program\n");
	gpioTerminate();
	return 0;
	}
}


void receiving(int gpio, int level, uint32_t tick)
{
	for(int i = 0; i < size*sampling; i++){
	file[i] = gpioRead(2);
	gpioDelay(time_transmission/sampling);
	}
	k++;
}
