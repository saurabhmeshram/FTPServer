#include <stdio.h>
int main()
{
	char *ptr = malloc(60);
	char *p1, *p2;
	fgets(ptr, 60, stdin);
	p1 = strtok(ptr, " ");
	printf("[%s]\n", p1);	
	p2 = strtok(NULL, " ");
	printf("[%s]\n", p2);	
	return 0;
}
