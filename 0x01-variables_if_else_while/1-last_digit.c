#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * main - assigns a random number to int n everytime
 * it executes, and prints it
 * Return: Always 0 (Success)
 */

int main(void)
{
	int n;
	int last_digit;

	srand(time(0));
	n = rand() - RAND_MAX / 2;
	last_digit = n % 10;
	printf("Last digit of %d is %d and is ");
	if (last_digit > 5)
		printf("greater than 5\n", n, last_digit);
	else if (last_digit == 0)
		printf("0\n", n, last_digit);
	else if (last_digit < 6 && n != 0)
		printf("less than 6 and not 0\n", n, last_digit);
	return (0);
}