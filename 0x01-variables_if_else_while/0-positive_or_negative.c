#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - this is the main of program.
 * rand() - function giving a random number.
 * return 0: that means the program Always return 0 (success).
*/

int main(void)
{
	int n;

	srand(time(0));
	n = rand() - RAND_MAX / 2;
	if ( n > 0 ){
		printf("%d is positive\n",n);
	} else if ( n == 0 ){
		printf("%d is zero\n",n);
	} else 
		printf("%d is negative\n",n);

	return (0);
}
