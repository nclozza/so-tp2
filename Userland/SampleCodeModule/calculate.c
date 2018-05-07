#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#define R 0
#define G 255
#define B 255

int calculateVerifications(int words, char *input2, char *input3)
{
	if (isNum(input2) == 2 || isNum(input3) == 2)
	{
		sysPrintString("Wrong parameters for calculate: Numbers must be integer\n", CB, CG, CR);
		return 0;
	}
	if (words != 4 || !isNum(input2) || !isNum(input3))
	{
		//veryfing that there are four inputs and that the last two are numbers
		sysPrintString("Wrong parameters for calculate\n", CB, CG, CR);
		return 0;
	}
	return 1;
}

int calculate(char *func, int param1, int param2)
{

	int (*operations[4])(int x, int y);
	operations[0] = add;
	operations[1] = subtract;
	operations[2] = multiply;
	operations[3] = divide;
	char *operationsName[4] = {"add", "subtract", "multiply", "divide"};

	for (int i = 0; i < 4; ++i)
	{
		if (strcmp(func, operationsName[i]) == 0)
		{
			return operations[i](param1, param2);
		}
	}

	return 0;
}

int runCalculate(int argc, char *argv[])
{
	if(argc!=5)
		return 1;
	int words = toInt(argv[1]);
	char* input01 = argv[2];
	char* input02 = argv[3];
	char* input03 = argv[4];

	int ver = calculateVerifications(words, input02, input03);

	if (ver)
	{
		int input2 = toInt(input02);
		int input3 = toInt(input03);

		int ans = calculate(input01, input2, input3);

		sysPrintString("Calculated: ", 255, 255, 0);
		sysPrintInt(ans, 255, 255, 0);
		sysPrintString("\n", 255, 255, 0);
	}
	return 0;
}