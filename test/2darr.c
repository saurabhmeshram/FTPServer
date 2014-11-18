#include <stdio.h>
int main()
{
	char *ptr, *cmd = malloc(100);
	int j = 0;

	char *arr[5];
	arr = (char **) malloc(sizeof(char *));

	int i;
	for(i=0; i<5; i++)
		*(arr + i) = malloc (sizeof(char) * 40);

	fgets(cmd, 1000, stdin);
	ptr = strtok(cmd, " ");
	do{
		printf("Token: [%s]\n", ptr);
		memcpy(*(arr+j), ptr, strlen(ptr));
		j++;
	}while(ptr = strtok(NULL, " "));

	printf("\n\n\n");
	for(i=0; i<5; i++)
	{
		printf("[%s]\n", *(arr + i));
	}
}
