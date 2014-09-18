#include <stdio.h>
int main()
{
    struct test
    {
        int k;
        char c;
    };
	struct test t;
	printf("Sizeof[%d]\n", sizeof(t));
return 0;
}
