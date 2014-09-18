#include <stdio.h>
int main()
{
	fun1() - (fun2()/fun3());
	return 0;
	
}

void fun1(void)
{
	printf("[%s]\n",__func__);
}

void fun2(void)
{
	printf("[%s]\n",__func__);
}

void fun3(void)
{
	printf("[%s]\n",__func__);
}
