#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
static int timeZone = -3;

void startShell()
{
	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;
	// int* page = (int*)sysMalloc(100);
	// sysPrintInt(*page,0,155,255);
	// sysPrintString("\n",CB,CG,CR);
	// *page = 12;
	// sysPrintInt(*page,0,155,255);
	// sysPrintString("\n",CB,CG,CR);
	// sysFree(page);
	// sysPrintInt(*page,0,155,255);
	sysPrintString("$> ", CB, CG, CR);

	while (isRunning)
	{

		sysGetChar(&ch);
		if (counter < MAX_WORD_LENGTH || ch == '\n' || ch == '\b')
		{

			sysWriteChar(ch, B, G, R);

			string[counter] = ch;
			(ch != 0) ? counter++ : counter;

			if (ch == '\n')
			{
				reset(lastString, strleng(lastString));
				copy(lastString, string, strleng(string) - 1);
				callFunction(string);
				if (isRunning)
					sysPrintString("$> ", CB, CG, CR);
				reset(string, strleng(string));
				counter = 0;
			}

			if (ch == '\b')
			{
				(counter != 0) ? string[counter--] = 0 : counter;
				(counter != 0) ? string[counter--] = 0 : counter;
			}
			if (ch == 15 && counter == 1)
			{ //UPARROW
				int len = strleng(lastString);
				sysPrintString(lastString, B, G, R);
				copy(string, lastString, len);
				counter = len;
			}
			if (ch == 14)
			{
				while (counter)
				{
					sysWriteChar('\b', B, G, R);
					(counter != 0) ? string[counter--] = 0 : counter;
					(counter != 0) ? string[counter] = 0 : counter;
				}
			}
		}
	}
}

int callFunction(char *buffer)
{
	if (buffer == NULL)
	{
		return 1;
	}

	int wordLength = 0;
	int words = 0;
	char input[MAX_WORDS][MAX_WORD_LENGTH] = {{0}};
	char *aux = buffer;
	int foreground = 0;
	if(*aux=='&')
	{
		foreground = 1;
		aux++;
	}
	if(foreground==1)
		sysPrintString("foreground true\n",0,155,255);
	while (*aux != '\0' && wordLength < MAX_WORD_LENGTH)
	{
		if (*aux == ' ' || *aux == '\n')
		{
			input[words][wordLength] = '\0';
			wordLength = 0;
			words++;
		}
		else
		{
			input[words][wordLength] = *aux;
			wordLength++;
		}

		aux++;
	}

	if (strcmp(input[0], "echo") == 0)
	{
		sysPrintString("called echo\n",0,155,255);
		//call echo.c con input, words
	}
	else if (strcmp(input[0], "setFontColor") == 0)
	{
		sysPrintString("called setFontColor\n",0,155,255);
		if (words != 2)
		{
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);
			return 1;
		}
		if (strcmp(input[1], "red") == 0)
		{
			R = 255;
			B = 0;
			G = 0;
		}
		else if (strcmp(input[1], "green") == 0)
		{
			R = 0;
			B = 0;
			G = 255;
		}
		else if (strcmp(input[1], "blue") == 0)
		{
			R = 0;
			B = 255;
			G = 0;
		}
		else if (strcmp(input[1], "default") == 0)
		{
			R = DR;
			B = DB;
			G = DG;
		}
		else
		{
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);
			return 1;
		}

		sysPrintString("Set font color\n", B, G, R);

		return 0;
	}
	else if (strcmp(input[0], "clear") == 0)
	{
		sysPrintString("called clear\n",0,155,255);
		//call clear.c con words
	}
	else if (strcmp(input[0], "opcode") == 0)
	{
		if (words != 1)
		{
			sysPrintString("No extra parameters for opcode\n", CB, CG, CR);
			return 1;
		}
		opcodeGenerator();
		return 0;
	}
	else if (strcmp(input[0], "calculate") == 0)
	{
		sysPrintString("called calculate\n",0,155,255);
		//call calculate.c con words, input[1], input[2], input[3]
	}
	else if (strcmp(input[0], "help") == 0)
	{
		sysPrintString("called help\n",0,155,255);
		//call help.c con words, input[1]
	}
	else if (strcmp(input[0], "exit") == 0)
	{
		if (words != 1)
		{
			sysPrintString("No extra parameters for exit\n", CB, CG, CR);

			return 1;
		}
		sysClear();
		sysPrintString("See you soon", CB, CG, CR);

		isRunning = 0;

		return 0;
	}
	else if (strcmp(input[0], "plot") == 0)
	{
		sysPrintString("called plot\n",0,155,255);
		//call plot.c con input, words
	}
	else if (strcmp(input[0], "displayTime") == 0)
	{
		sysPrintString("called displayTime\n",0,155,255);
		//call displayTime.c con words, timeZone
	}
	else if (strcmp(input[0], "setTimeZone") == 0)
	{
		sysPrintString("called setTimeZone\n",0,155,255);
		//call setTimeZone.c con words, input[1], timeZone
		timeZone = -3;
		
	}
	else
	{
		sysPrintString("Wrong input\n", CB, CG, CR);

		return 1;
	}

	return 1;
}






