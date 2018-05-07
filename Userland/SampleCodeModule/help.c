#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#define R 0
#define G 255
#define B 255

int help(int words, char* input1)
{

	if (words > 2)
		{
			sysPrintString("No extra parameters for help\n", CB, CG, CR);

			return 1;
		}
		if (words == 2)
		{
			if (strcmp(input1, "echo") == 0)
			{
				sysPrintString(ECHO_INS, B, G, R);
			}
			else if (strcmp(input1, "displayTime") == 0)
			{
				sysPrintString(DISPLAY_TIME_INS, B, G, R);
			}
			else if (strcmp(input1, "setTimeZone") == 0)
			{
				sysPrintString(SET_TIME_ZONE_INS, B, G, R);
			}
			else if (strcmp(input1, "setFontColor") == 0)
			{
				sysPrintString(SET_FONT_COLOR_INS, B, G, R);
			}
			else if (strcmp(input1, "clear") == 0)
			{
				sysPrintString(CLEAR_INS, B, G, R);
			}
			else if (strcmp(input1, "calculate") == 0)
			{
				sysPrintString(CALCULATE_INS, B, G, R);
			}
			else if (strcmp(input1, "exit") == 0)
			{
				sysPrintString(EXIT_INS, B, G, R);
			}
			else if (strcmp(input1, "plot") == 0)
			{
				sysPrintString(PLOT_INS, B, G, R);
			}
			else if (strcmp(input1, "opcode") == 0)
			{
				sysPrintString(OPCODE_INS, B, G, R);
			}
			else
			{
				sysPrintString("Not a valid command\n", CB, CG, CR);
			}
		}
		else
		{
			sysPrintString(helpIns, B, G, R);
		}

	return 0;
}