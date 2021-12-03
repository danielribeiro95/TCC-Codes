#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 21

#define TIME 500

phtread_mutex_t mutex1;

int wave_id,header_id,flag;
int taille_phrase,taille_trame;

void *thread_cmd()
{
	if(flag == 1)
	{
		gpioWaveTxSend(header_id,PI_WAVE_MODE_ONE_SHOT);
	}
}

int main()
{
	pthread th1;

	int val, i;


	FILE *file_read;
	file_read = fopen("Doc1.txt","r");

   	fseek(file_read,0,SEEK_END);  //Get the size of the file
	int size = ftell(file_read); // Ignore the last element (end of file)
	printf("\nSize = %d \n", size);
	rewind(file_read);

	char file_char[size];

	for (int i = 0; i < size ; i++){
        val[i] = fgetc(file_read);
        printf("%d  ",val[i]);
   	}

	taille_phrase = size;
	taille_trame = taille_phrase*8*2+7;

	gpioPulse_t pulse[taille_trame];


	if (gpioInitialise() < 0)
{}
	if(gpioSetMode(PIN,PI_OUTPUT)==0)
{}

	pthread_mutex_init(&mutex1,NULL);

	if(pthread_create(&th,NULL,thread_cmd,NULL)<0)
{}

	int convD;
	int jj,ii,inc;

	for(jj = 0; jj<4;jj++)

}
