#include "shell.h"

/**
 * kel_print - prints command to the standard output
 * @format: string to be printed
 * Return: void
 */

void kel_print(const char *format)
{
	write(STDOUT_FILENO, format, strlen(format));
}
