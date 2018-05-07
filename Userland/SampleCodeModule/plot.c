#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#define R 0
#define G 255
#define B 255


int plot(char input[4][MAX_WORD_LENGTH], int words)
{
	if (words != (GRAPH_PARAMETERS + 1))
	{
		sysPrintString("Wrong amount of parameters for plot command\n\
		Use command help for guidelines\n",
									 CB, CG, CR);

		return 2;
	}

	for (int i = 1; i <= GRAPH_PARAMETERS; i++)
	{
		if (!isNum(input[i]))
		{
			sysPrintString("Wrong parameters passed to plot command\n\
			Use command help for guidelines\n",
										 CB, CG, CR);

			return 2;
		}
	}

	graphMain(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]));
	
	return 0;
}