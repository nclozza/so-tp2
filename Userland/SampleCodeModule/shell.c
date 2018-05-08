#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#include "semaphoreUserlandTests.h"
#include "commands.h"

#define STEP 10
#define BUFFERSIZE 1024

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
static command commands[] = {
	{"help\0",help},
	{"help\n",help},
	{"echo\0",echo},
	{"echo\n",echo},
	{"displayTime\n",displayTime},
	{"setTimeZone\n",setTimeZone},
	{"setFontColor\n",setFontColor},
	{"clear\n",clear},
	{"calculate\0",calculate},
	{"calculate\n",calculate},
	{"plot\0",plot},
	{"plot\n",plot},	
	{"exit\n",exit},
	{"opcode\n",opcode},
	{"prodcons\n",prodcons}
};

//static int timeZone = -3;
void parseParams(char * command, int * argc, char *** argv);

void startShell()
{
	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;
	//runUserlandSemaphoreTests();
	
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

	int words;
	char** argv;	
	parseParams(buffer,&words,&argv);

	//call echo.c con words,input[1],input[1],...,input[words]
	//call clear.c con words
	//call calculate.c con words, input[1], input[2], input[3]
	//call help.c con words, input[1]
	//call plot.c con input, words
	//call displayTime.c con words, timeZone
	//call setTimeZone.c con words, input[1], timeZone

	
	int i,valid=0;	
	for(i = 0; i < CMD_SIZE && valid==0; i++)
	{
		if(strcmp(argv[0],commands[i].name)==0)
		{						

			int status = commands[i].function(words,argv);
			if(status == ERROR)
			{
				sysPrintString("Error\n",0,155,255);
				return ERROR;
			}
			else if(status == EXITCODE)
			{
				isRunning = 0;				
				for(int i = 0 ; i < words; i++)
				{
					sysFree((uint64_t)argv[i]);
				}
				sysFree((uint64_t)argv);
			}			
			valid = 1;	
		}
	}	

	if(valid==0)
	{		
		sysPrintString("Wrong input\n", CB, CG, CR);
	}

	return 1;
}

void parseParams(char * command, int * argc, char *** argv) {
  char buffer[BUFFERSIZE];
  int count = 0, size = 0, i = 0, j = 0;
  do {
    if(command[i] != ' ' && command[i] != 0) 
    {
      buffer[j] = command[i];
      j++;
    } 
    else if(j != 0) 
    {
      if(size - count == 0) 
      {
        size += STEP;
        (*argv) = (char **)sysMalloc(sizeof(void*)*size);
      }
      (*argv)[count] = (char*)sysMalloc(sizeof(char)*(j+1));
      for (int k = 0; k < j; k++) 
      {
        (*argv)[count][k] = buffer[k];
      }
      (*argv)[count][j] = 0; //Null terminated
      count++;
      j = 0;
    }
  } while (command[i++] != 0);

  (*argc) = count;
}
// int wordLength = 0;
	// int words = 0;
	// char input[MAX_WORDS][MAX_WORD_LENGTH] = {{0}};
	// char *aux = buffer;
	// int foreground = 0;
	// if(*aux=='&')
	// {
	// 	foreground = 1;
	// 	aux++;
	// }
	// if(foreground==1)
	// 	sysPrintString("foreground true\n",0,155,255);

	// while (*aux != '\0' && wordLength < MAX_WORD_LENGTH)
	// {
	// 	if (*aux == ' ' || *aux == '\n')
	// 	{
	// 		(*argv)[wordLength] = '\0';
	// 		wordLength = 0;
	// 		words++;
	// 	}
	// 	else
	// 	{
	// 		input[words][wordLength] = *aux;
	// 		wordLength++;
	// 	}

	// 	aux++;
	// }