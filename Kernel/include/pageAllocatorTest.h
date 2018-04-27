#ifndef PAGEALLOCATORTEST_H_
#define PAGEALLOCATORTEST_H_
void whenAPageIsRequested();
void thenACorrectPageAddressIsReturned();
void givenARequestedPage();
void whenPageIsReleased();
void thenPageIsInsertedInStack();
void thenIndexInStackDecreases();
void testAllocatePageWhenStackEmpty();
void testReleasePage();
void testAllocatePageWhenStackNotEmpty();
void runPageAllocatorTests();

#endif