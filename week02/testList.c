// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLList.h"
// should be declared in DLList.h,
// but since it is not submitted, declared here
char *DLListLast (DLList L);
char *DLListFirst (DLList L);
int strEqual(char *a, char *b);

int strEqual(char *a, char *b) {
	return strcmp(a, b) == 0;
}

#define NUM_TEST_ITEMS 4
static const char *testItems[] = {"owo", "umu", ":3", "xd"};

void checkCurrent (DLList L, char *val) 
{
	printf ("Checking current element: %s found, %s expected\n", DLListCurrent(L), val);
	assert (strEqual(DLListCurrent(L), val));
}

void checkLast (DLList L, char *val) 
{
	printf("Checking last element: %s found, %s expected\n", DLListLast(L), val);
	assert ( strEqual(DLListLast(L), val));
} 

void checkFirst (DLList L, char *val) 
{
	printf("Checking first element: %s found, %s expected\n", DLListFirst(L), val);
	assert ( strEqual(DLListFirst(L), val));
} 

void checkLength (DLList L, size_t size) 
{
	printf("Checking length: %d elements found, %d elements expected\n", DLListLength (L), size);
	assert (DLListLength(L) == size);
}

void checkValid (DLList L) {
	assert (validDLList (L));
}


void checkAllBefore (FILE *out) {
	DLList myList = newDLList();
	checkValid (myList);

	//tests:
	// we need to test DLListBefore
	// DLListAFter
	// DLListDelete
	//DLListBefore(myList, "");

	// testing DLListBefore
	// test inserting into a empty list
	// this should also set current = the first element
	fprintf(out, "adding an element before, uwu\n");
	DLListBefore (myList, "uwu");
	assert (validDLList(myList));

	checkLength (myList, 1);
	checkFirst (myList, "uwu");
	checkCurrent (myList, "uwu");
	checkLast (myList, "uwu");
	putDLList (out, myList);
	
	printf("\n");

	printf("Adding a number of items before:\n");
	// adding a number of items
	// then test that the items got successfully items
	for (int i = 0; i < NUM_TEST_ITEMS; i++ )
	{
		// curritem, ... , uwu
		// note this inserts the items 
		// so that they are in reverse order
		// as it always insert the element at 
		// the front of list
		fprintf(out, "adding an element before, %s\n", testItems[i]);
		DLListBefore (myList, testItems[i]);
		putDLList (out, myList);

		checkFirst (myList, testItems[i]);
		checkCurrent (myList, testItems[i]);
		checkLength (myList, i + 2);
		checkValid (myList);
	}
	printf("\n");
	printf("testing the added items\n");
	for (int i=NUM_TEST_ITEMS-1; i>=0; i--) {
		// now check that the elements were saved
		// they should be in reverse order
		// as it was added before
		fprintf(out, "moving 1 forward\n");
		checkCurrent (myList, testItems[i]);
		DLListMove (myList, 1);
		putDLList(out, myList);
		checkValid (myList);

	}
	// should be at the end
	// check the item at the end
	fprintf(out, "moving 1 forward (at the end)\n");
	checkCurrent (myList, "uwu");
	DLListMove (myList, 1);
	checkValid (myList);
	putDLList(out, myList);

	// also test inserting in the middle
	fprintf(out, "moving back 3\n");
	DLListMove(myList, -3);
	checkCurrent (myList, ":3");
	putDLList(out, myList);
	checkValid(myList);

	fprintf(out, "inserting a 'sword' in the before\n");
	DLListBefore(myList, "sword");
	putDLList(out, myList);
	checkCurrent (myList, "sword");
	checkValid(myList);

	// and test in the end
	fprintf(out, "moving to end\n");
	DLListMove(myList, DLListLength(myList)+1);
	putDLList(out, myList);
	checkValid(myList);

	fprintf(out, "inserting a 'shield' before last item\n");
	DLListBefore(myList, "shield");
	putDLList(out, myList);
	checkCurrent (myList, "shield");
	checkValid(myList);

	freeDLList(myList);
}

void checkAllAfter (FILE *out) {
	DLList myList = newDLList();
	checkValid (myList);

	//tests:
	// we need to test DLListBefore
	// DLListAFter
	// DLListDelete
	//DLListBefore(myList, "");

	// testing DLListBefore
	// test inserting into a empty list
	// this should also set current = the first element
	fprintf(out, "adding an element after, uwu\n");
	DLListAfter (myList, "uwu");
	assert (validDLList(myList));

	checkLength (myList, 1);
	checkFirst (myList, "uwu");
	checkCurrent (myList, "uwu");
	checkLast (myList, "uwu");
	putDLList (out, myList);
	
	printf("\n");

	printf("Adding a number of items before:\n");
	// adding a number of items
	// then test that the items got successfully items
	for (int i = 0; i < NUM_TEST_ITEMS; i++ )
	{
		// curritem, ... , uwu
		// note this inserts the items 
		// so that they are in reverse order
		// as it always insert the element at 
		// the front of list
		fflush(out);
		fprintf(out, "adding an element after, %s\n", testItems[i]);
		
		DLListAfter (myList, testItems[i]);
		putDLList (out, myList);

		checkLast (myList, testItems[i]);
		checkCurrent (myList, testItems[i]);
		checkLength (myList, i + 2);
		checkValid (myList);
	}
	printf("\n");
	fflush(out);
	printf("testing the added items\n");
	for (int i=NUM_TEST_ITEMS-1; i>=0; i--) {
		// now check that the elements were saved
		// they should be in reverse order
		// as it was added before
		checkCurrent (myList, testItems[i]);
		fprintf(out, "moving 1 backwards\n");
		DLListMove (myList, -1);
		putDLList(out, myList);
		checkValid (myList);
		fflush(out);
	}
	// should be at the start
	// check the item at the start
	checkCurrent (myList, "uwu");
	checkValid (myList);
	fflush(out);

	// also test inserting in the middle
	fprintf(out, "moving forward 3\n");
	DLListMove(myList, 3);
	checkCurrent (myList, ":3");
	putDLList(out, myList);
	checkValid(myList);

	fprintf(out, "inserting a 'sword' in after\n");
	DLListAfter(myList, "sword");
	putDLList(out, myList);
	checkCurrent (myList, "sword");
	checkValid(myList);

	// and test in the end
	fprintf(out, "moving to end\n");
	DLListMove(myList, DLListLength(myList)+1);
	putDLList(out, myList);
	checkValid(myList);

	fprintf(out, "inserting a 'shield' in after\n");
	DLListAfter(myList, "shield");
	putDLList(out, myList);
	checkCurrent (myList, "shield");
	checkValid(myList);

	freeDLList(myList);
}

void checkAllDelete (FILE *out) {
	DLList myList = newDLList();
	checkValid (myList);
	const char *items[] = {"1", "2", "3", "4", "5"};
	for (int i=0; i<5; i++) {
		DLListAfter(myList, items[i]);
	}
	checkValid(myList);
	DLListMove(myList, -DLListLength(myList));
	fprintf(out, "loaded the list\n");
	putDLList(out, myList);

	// delete an element from the beginning
	fprintf(out, "deleting first element\n");
	DLListDelete(myList);
	putDLList(out, myList);
	checkCurrent(myList, "2");

	// delete an element from the middle
	fprintf(out, "moving 1 forward\n");
	DLListMove(myList, 1);
	checkCurrent(myList, "3");
	putDLList(out, myList);

	fprintf(out, "deleting an element in the middle\n");
	DLListDelete(myList);
	putDLList(out, myList);
	checkCurrent(myList, "4");

	// delete an element from the end
	fprintf(out, "moving 1 forward\n");
	DLListMove(myList, 1);
	checkCurrent(myList, "5");
	putDLList(out, myList);

	fprintf(out, "deleting an element from the end\n");
	DLListDelete(myList);
	putDLList(out, myList);
	checkCurrent(myList, "4");

	fprintf(out, "deleting all elements\n");
	while (DLListLength(myList) != 0) {
		DLListDelete(myList);
		
	}
	putDLList(out, myList);

	fprintf(out, "deleting when empty\n");
	// delete when its empty
	DLListDelete(myList);
	putDLList(out, myList);

	freeDLList(myList);
}


int main (void)
{
	FILE *out = fopen("debug.txt", "w");
	assert(out!=NULL);
	//DLList myList = getDLList (stdin);
	fprintf(out, "creating new list:\n");
	checkAllBefore(out);
	fprintf(out, "creating new list:\n");
	checkAllAfter(out);
	fprintf(out, "creating new list:\n");
	checkAllDelete(out);


	
	return EXIT_SUCCESS;
}
