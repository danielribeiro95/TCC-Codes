#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pigpio.h>
//We're gonna use GPIO21 as output

#define GPIO 21

int time_half_bit = 500; // Time in Microseconds
int parity = 1;

void transmission()
{



	if (gpioInitialise()<0)
	{
		printf("Initialisation Failed \n");
	}


	else
	{

	// ------------------------------------ CONVERSION -----------------------------------

	gpioSetMode(GPIO,1); //21 => Output

	FILE *file_read;
	file_read = fopen("Doc1_bin.txt","r");

	fseek(file_read,0,SEEK_END);  //Get the size of the file
	int size = ftell(file_read)-1; // Ignore the last element (end of file)
	printf("\nSize = %d \n", size);
	rewind(file_read);

	_Bool file[size+parity]; //Contains the file

	file[0] = 1;
	for(int i = 1; i<size+parity-1; i++){
	file[i] = fgetc(file_read) - '0';
	}


	printf("\n\nSize with parity bit 1: %d \n",size+parity);


	fclose(file_read);


	// -------------------------------------------- TRANSMISSION ------------------------------------------------

	gpioDelay(2000000);

	for (int i = 0; i < size+parity; i++){
	if(file[i] == 1){
	gpioWrite(GPIO,1);
	gpioDelay(time_half_bit);
	gpioWrite(GPIO,0);
	gpioDelay(time_half_bit);
	}
	else{
	gpioWrite(GPIO,0);
	gpioDelay(time_half_bit);
	gpioWrite(GPIO,1);
	gpioDelay(time_half_bit);
	}

	}

	_Bool k = 0;
	for(int i = 0; i < 10000; i++)
	{
	gpioWrite(GPIO,k);
	k = !k;
	}

	gpioWrite(GPIO,0);

	gpioTerminate();
	}

}
