// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLList.h"

int main (void)
{
	//DLList myList = getDLList (stdin);
	DLList myList = newDLList();
	//DLListBefore(myList, "");
	assert (validDLList (myList));

	// TODO: more tests needed here

	char *tests[] = {"test", "abcd", "owo", "1234"};
	int testsLength = 4;
	int move = 0;

	// added in reverse to have the right order
	for (int i = testsLength-1; i >= 0; i--)
	{
		DLListAfter(myList, tests[i]);
		assert (validDLList (myList));
	}

	if (DLListLength(myList) > testsLength)
	{
		move = 1;
		DLListMove(myList, 1);
	}

	for (int i = 0; i < testsLength; i++)
	{
		printf("current: %s\n", DLListCurrent(myList));
		printf("array: %s\n", tests[i]);
		fflush(stdout);
		assert(strcmp(DLListCurrent(myList), tests[i]) == 0);

		
		DLListMove(myList, 1);
	}

	for (int i = testsLength-1; i >= 0; i--)
	{
		DLListBefore(myList, tests[i]);
		assert (validDLList (myList));
	}

	for (int i = 0; i < testsLength; i++)
	{
		DLListMove(myList, -1);
		assert(strcmp(DLListCurrent(myList), tests[i]) == 0);
	}

	//delete
	for (int i = 0; i < testsLength*2; i++)
	{
		printf(DLListCurrent(myList));
		printf("\n");
		DLListDelete(myList);
		assert (validDLList (myList));
	}
	/*DLListMove(myList, -4);
	for (int i = 0; i < testsLength; i++)
	{
		DLListDelete(myList);
		assert (validDLList (myList));
	}*/
	//assert(strcmp(DLListCurrent(myList), ))

	putDLList (stdout, myList);
	freeDLList (myList);
	return EXIT_SUCCESS;
}
