#include "testlib.h"
#include "pageallocator.h"
#include "videoDriver.h"

void whenAPageIsRequested();
void thenACorrectPageAddressIsReturned();
void givenARequestedPage();
void whenPageIsReleased();
void thenPageIsInsertedInStack();
void thenIndexInStackDecreases();


uint64_t requestedPage = 0; 
uint64_t requestedPage2 = 0; 
int index = 0;

void testAllocatePageWhenStackEmpty()
{
	whenAPageIsRequested();
	thenACorrectPageAddressIsReturned();
}

void testReleasePage()
{
	givenARequestedPage();
	whenPageIsReleased();
	thenPageIsInsertedInStack();
}

void testAllocatePageWhenStackNotEmpty()
{
	whenAPageIsRequested();
	thenACorrectPageAddressIsReturned();
	thenIndexInStackDecreases();
}


void whenAPageIsRequested()
{
	index = getIndexInStack();
	requestedPage = getAvailablePage();
}

void thenACorrectPageAddressIsReturned()
{
	checkAreNotEqual(requestedPage,0);
}
void givenARequestedPage()
{
	requestedPage2 = getAvailablePage();
}
void whenPageIsReleased()
{
	releasePage(requestedPage2);
}
void thenPageIsInsertedInStack()
{
	if(requestedPage2 == peekAvailablePage())
	{
		printString("Ok\n",0,255,0);
	}
	else
	{
		printString("Page not inserted in stack\n",0,0,255);
	}
}
void thenIndexInStackDecreases()
{
	checkAreEqual(index-1,getIndexInStack());
}

void runPageAllocatorTests()
{
	initializePageAllocator();
	printString("Running tests...\n",128,128,128);
	printString("Testing allocating page when stack is empty...\n",128,128,128);
	testAllocatePageWhenStackEmpty();
	printString("Testing release of page...\n",128,128,128);
	testReleasePage();
	printString("Testing allocating page when stack is not empty...\n",128,128,128);
	testAllocatePageWhenStackNotEmpty();
	printString("Finished testing\n",128,128,128);
}