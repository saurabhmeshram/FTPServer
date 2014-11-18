#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_PATH "./file" 
int main()
{
	FILE *fp = NULL;	
	if(-1 == (fp = fopen(FILE_PATH, "r")))
		printf("Open failed\n");
	char *buf = malloc(2048);

	fgets(buf, 2048, fp);
	
	printf("%s\n", buf);

}
