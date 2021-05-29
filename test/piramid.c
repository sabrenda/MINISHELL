#include <stdio.h>




void recursive(int i)
{
	int count = 1;
	if (i == 0)
		return ;
	recursive(i - 1);
	while(count < i)
		printf("%d", count++);
	printf("\n");
}

int main()
{
	recursive(10);
	return (0);
}
