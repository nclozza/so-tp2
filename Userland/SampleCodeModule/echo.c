#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#define R 0
#define G 255
#define B 255
int echo(char input[][MAX_WORD_LENGTH], int words)
{

	for (int i = 1; i < (words + 1); i++)
	{
		sysPrintString(input[i], B, G, R);
		sysPrintString(" ", B, G, R);
	}

	sysPrintString("\n", B, G, R);

	return 0;
}