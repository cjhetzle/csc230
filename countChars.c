#include <stdio.h>
#include <stdlib.h>

int main()
{
	int count = 0;

	int ch;
	while (( ch = getchar() ) != EOF)
		count++;

	printf("%d\n", count);

	return EXIT_SUCCESS;
}