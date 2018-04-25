#include <stdlib.h>
#include <stdio.h>
#include "testlib.h"
#include "semaphore.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"


void checkIsNotNull(void* value)
{
	if(value == NULL)
	{
		fail("Expected: a non null value, got: a null value ");
	}
	else
	{
		ok("Checked is not null");
	}
}

void checkIsNotZero(int value)
{
	if(value == 0)
	{
		fail("Expected: a non zero value, got: a zero value");
	}
	else
	{
		ok("Checked is not zero");
	}
}

void checkSizeOfSemaphoreList(int mysize, int size)
{
	if(size != mysize)
	{
		fail("Expected: list size to remain the same, got: difference in size");
	}
	else
	{
		ok("Checked size of list");
	}
}
void ok(char* success)
{
	printf(ANSI_COLOR_GREEN ":) %s" ANSI_COLOR_RESET "\n",success);
}

void fail(char* withError)
{
	printf(ANSI_COLOR_RED "	%s" ANSI_COLOR_RESET "\n",withError);
}