#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *file_read;
	file_read = fopen("Doc1.txt","r");
	char single_line[150];

	while(!feof(file_read))
	{
		fgets(single_line,150,file_read);
		puts(single_line);

	}


	fclose(file_read);

	return 0;
}
