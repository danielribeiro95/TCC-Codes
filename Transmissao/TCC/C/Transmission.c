#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pigpio.h>
//We're gonna use GPIO2 as output

int time_transmission = 10000; // Time in Microseconds
int parity = 6;

void transmission()
{



	if (gpioInitialise()<0)
	{
		printf("Initialisation Failed \n");
	}


	else
	{

	// ------------------------------------ CONVERSION -----------------------------------

	gpioSetMode(2,1); //2 => Output

	FILE *file_read;
	file_read = fopen("Doc1_bin.txt","r");

	fseek(file_read,0,SEEK_END);  //Get the size of the file
	int size = ftell(file_read)-1; // Ignore the last element (end of file)
	printf("\nSize = %d \n", size);
	rewind(file_read);

	int file[size]; //Contains the file

	for(int i = 0; i<size; i++){
	file[i] = fgetc(file_read) - '0';
//	printf("%d", file[i]);		//Reading into the file the bits
	}


	int file_aux[size+parity];
	file_aux[0]=0;
	file_aux[1]=1;
	file_aux[2]=0;
	file_aux[size+parity-1] = 0;
	file_aux[size+parity-2] = 1;
	file_aux[size+parity-3] = 0;
	for(int i = 3; i<size+(parity/2);i++){
		file_aux[i] = file[i-parity/2];
	}


	printf("\n\nSize with dobule parity word 010: %d \n",size+parity);


	fclose(file_read);


	// -------------------------------------------- TRANSMISSION ------------------------------------------------

	for (int i = 0; i < size+parity; i++){
	gpioWrite(2,file_aux[i]);
	gpioDelay(time_transmission);
	}

	printf("\n");
	gpioWrite(2,0);
	gpioTerminate();
	}
}
