#include <stdint.h>
#include "commands.h"
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#include "prodcons.h"
#include "calculate.h"
static int R = DR;
static int G = DG;
static int B = DB;
static int red  = 7;
static int green = 8;
static int blue = 9;
static int defaultColor = 10;
int timeZone = -3;

int help(int argc,char* argv[])
{
	if(argc>2)
		return ERROR;	

	if (argc == 2)
	{
		char* input1 = argv[2];
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
int echo(int argc,char* argv[])
{
	for (int i = 1; i < (argc + 1); i++)
	{
		sysPrintString(argv[i], B, G, R);
		sysPrintString(" ", B, G, R);
	}

	sysPrintString("\n", B, G, R);

	return 0;
}

int clear(int argc,char* argv[])
{	
	if (argc != 1)
	{
		sysPrintString("No extra parameters for clear\n", CB, CG, CR);

		return ERROR;
	}

	sysClear();
	return 0;
}

int calculate(int argc, char *argv[])
{
	/*calculate operation n1 n2*/
	if(argc!=4)
		return 1;
	char* input01 = argv[1];
	char* input02 = argv[2];
	char* input03 = argv[3];

	int ver = calculateVerifications(argc, input02, input03);

	if (ver)
	{
		int input2 = toInt(input02);
		int input3 = toInt(input03);

		int ans = runCalculate(input01, input2, input3);

		sysPrintString("Calculated: ", 255, 255, 0);
		sysPrintInt(ans, 255, 255, 0);
		sysPrintString("\n", 255, 255, 0);
	}
	return 0;
}

int opcode(int argc,char* argv[])
{
	if (argc != 1)
	{
		sysPrintString("No extra parameters for opcode\n", CB, CG, CR);
		return ERROR;
	}
	opcodeGenerator();
	return 0;
}

int prodcons(int argc,char* argv[])
{
	if(argc!=1)
		return ERROR;
	runProdCons();
	return 0;
}

int plot(int argc,char* argv[])
{

	if (argc != (GRAPH_PARAMETERS + 1))
	{
		sysPrintString("Wrong amount of parameters for plot command\n\
		Use command help for guidelines\n",
									 CB, CG, CR);

		return 2;
	}

	for (int i = 1; i <= GRAPH_PARAMETERS; i++)
	{
		if (!isNum(argv[i]))
		{
			sysPrintString("Wrong parameters passed to plot command\n\
			Use command help for guidelines\n",
										 CB, CG, CR);

			return 2;
		}
	}

	graphMain(toFloat(argv[1]), toFloat(argv[2]), toFloat(argv[3]));
	
	return 0;
}

int displayTime(int argc, char *argv[])
{
	if (argc != 1)
	{
		sysPrintString("Wrong parameters: displayTime\n", CB, CG, CR);
		return ERROR;
	}
	int timeBuff[6];

	sysGetTime(timeBuff);
	sysPrintInt((timeBuff[2] + timeZone) % 24, B, G, R);
	sysPrintString(":", B, G, R);
	if (timeBuff[1] / 10 == 0)
		sysPrintString("0", B, G, R);
	sysPrintInt(timeBuff[1], B, G, R);
	sysPrintString(":", B, G, R);
	if (timeBuff[0] / 10 == 0)
		sysPrintString("0", B, G, R);
	sysPrintInt(timeBuff[0], B, G, R);

	sysPrintString(" - ", B, G, R);
	if ((timeBuff[2] + timeZone) / 24 != 0)
		sysPrintInt(timeBuff[3] + 1, B, G, R);
	else
		sysPrintInt(timeBuff[3], B, G, R);

	sysPrintString("/", B, G, R);
	sysPrintInt(timeBuff[4], B, G, R);
	sysPrintString("/", B, G, R);
	sysPrintInt(timeBuff[5], B, G, R);
	sysPrintString("\n", B, G, R);
		
	return 0;
}

int setTimeZone(int argc, char *argv[])
{
	int input1 = toInt(argv[1]);
	if (argc != 2)
	{
		sysPrintString("Wrong parameters: setTimeZone timezone\n", CB, CG, CR);
		return ERROR;
	}
	else
	{
		if (input1 > 12 || input1 < -11)
		{
			sysPrintString("Timezone values must be between -11 and +12\n", CB, CG, CR);
			return ERROR;
		}
		timeZone = input1;
		return input1;
	}
}

int exit(int argc,char* argv[])
{
	return EXITCODE;
}

int setFontColor(int argc,char* argv[])
{
	if (argc != 2)
		{
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);
			return 1;
		}
		if (strcmp(argv[2], "red") == 0)
		{
			return red;
		}
		else if (strcmp(argv[2], "green") == 0)
		{
			return green;
		}
		else if (strcmp(argv[2], "blue") == 0)
		{
			return blue;
		}
		else if (strcmp(argv[2], "default") == 0)
		{
			return defaultColor;
		}
		else
		{
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);
			return 1;
		}

		sysPrintString("Set font color\n", B, G, R);	
}