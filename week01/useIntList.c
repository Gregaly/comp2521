// useIntList.c - testing IntList data type

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IntList.h"

int main (int argc, char *argv[])
{
	IntList myList = getIntList (stdin);

	assert (IntListOK (myList));

	IntList myOtherList = IntListSortedCopy (myList);

	showIntList (myOtherList);

	assert (IntListOK (myOtherList));
	assert (IntListIsSorted (myOtherList));

	freeIntList (myList);
	freeIntList (myOtherList);
	return EXIT_SUCCESS;
}
