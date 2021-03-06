// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "graph.h"
#include "html.h"
#include "set.h"
#include "stack.h"
#include "url_file.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
	//    }
	//    close the opened URL
	//    sleep(1)
	// }

	Graph web = newGraph(maxURLs);
	Set seen = newSet();
	Stack todo = newStack();

	// push the first url
	pushOnto(todo, strdup(firstURL));
	insertInto(seen, firstURL);

	// dfs search
	while (!emptyStack(todo) && nVertices(web) < maxURLs) {
		// the url to search
		char *url = popFrom(todo);
		printf("Current url: %s\n", url);
		printf("\ttotal urls stored: %zu\n", nVertices(web));

		// ensure in unsw network
		if (strstr(url, "unsw.edu.au") == NULL) continue;

		// error handling for network errors
		if (!(handle = url_fopen (url, "r"))) {
			fprintf (stderr, "Couldn't open %s\n", next);
			exit (1);
		}
		while (!url_feof (handle)) {
			// keep getting a full buffer of data each loop
			url_fgets (buffer, sizeof (buffer), handle);

			// initialize variables for html searching
			int pos = 0;
			char result[BUFSIZE];
			memset(result, 0, BUFSIZE);

			// search for new urls in the html buffer
			// result is a url found on the html page
			while ((pos = GetNextURL (buffer, url, result, pos)) > 0) {

				// this url needs to be copied, as
				// the result buffer is overwritten each loop
				
				// add edge between two urls iff the graph is not full of vertices
				// this is to prevent getting too big...
				if (nVertices(web) < maxURLs) {
					addEdge(web, url, result);
				}

				// if this url has not been seen before,
				// add it to the todo and seen stack/set
				// allowing algorithm to view those later
				if (!isElem(seen, result)) {
					printf ("\t\tNew URL, adding: %s\n", url);
					insertInto(seen, result);
					pushOnto(todo, result);
				}


				memset (result, 0, BUFSIZE);
			}
		}


		free(url);
		url_fclose (handle);
		sleep(1);
	}

	printf("----------\n Showing Graph \n ---------\n");
	showGraph(web, 0);
	
	// deallocate any memory in the set
	// todo lol
	dropStack(todo);
	dropSet(seen);
	dropGraph(web);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
