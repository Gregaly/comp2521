////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Map.c: an implementation of a Map type
// You can change this as much as you want!
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "Map.h"
#include "Places.h"

typedef struct vNode *VList;
struct vNode {
	LocationID  v;    // ALICANTE, etc
	TransportID type; // ROAD, RAIL, BOAT
	VList       next; // link to next node
};

struct map {
	int nV; // #vertices
	int nE; // #edges
	VList connections[NUM_MAP_LOCATIONS]; // array of lists
};

static void addConnections(Map);

// Create a new empty graph (for a map)
// #Vertices always same as NUM_PLACES
Map
newMap (void)
{
	Map g = malloc (sizeof *g);
	if (g == NULL) err (EX_OSERR, "couldn't allocate Map");

	(*g) = (struct map){
		.nV = NUM_MAP_LOCATIONS,
		.nE = 0,
		.connections = { NULL }
	};

	addConnections (g);
	return g;
}

// Remove an existing graph
void dropMap (Map g)
{
	// wait, what?
	if (g == NULL) return;

	for (int i = 0; i < g->nV; i++) {
		VList curr = g->connections[i];
		while (curr != NULL) {
			VList next = curr->next;
			free (curr);
			curr = next;
		}
	}
	free (g);
}

static VList insertVList (VList L, LocationID v, TransportID type)
{
	VList new = malloc (sizeof(struct vNode));
	if (new == NULL) err (EX_OSERR, "couldn't allocate vNode");
	(*new) = (struct vNode){ .v = v, .type = type, .next = L };
	return new;
}

static int inVList (VList L, LocationID v, TransportID type)
{
	for (VList cur = L; cur != NULL; cur = cur->next)
		if (cur->v == v && cur->type == type)
			return 1;

	return 0;
}

// Add a new edge to the Map/Graph
static void addLink (Map g, LocationID start, LocationID end, TransportID type)
{
	assert (g != NULL);

	// don't add edges twice
	if (inVList (g->connections[start], end, type)) return;

	g->connections[start] = insertVList(g->connections[start],end,type);
	g->connections[end] = insertVList(g->connections[end],start,type);
	g->nE++;
}

// Display content of Map/Graph
void showMap (Map g)
{
	assert (g != NULL);

	printf ("V=%d, E=%d\n", g->nV, g->nE);
	for (int i = 0; i < g->nV; i++)
		for (VList n = g->connections[i]; n != NULL; n = n->next)
			printf ("%s connects to %s by %s\n",
					idToName (i), idToName (n->v), transportToName (n->type));
}

// Return count of nodes
int numV (Map g)
{
	assert (g != NULL);
	return g->nV;
}

// Return count of edges of a particular type
int numE (Map g, TransportID type)
{
	assert (g != NULL);
	assert (0 <= type && type <= ANY);

	int nE = 0;
	for (int i = 0; i < g->nV; i++)
		for (VList n = g->connections[i]; n != NULL; n = n->next)
			if (n->type == type || type == ANY)
				nE++;

	return nE;
}

// Add edges to Graph representing map of Europe
static void addConnections (Map g)
{
#define IS_SENTINEL(x) ((x).v == -1 && (x).w == -1 && (x).t == ANY)
	for (int i = 0; ! IS_SENTINEL (CONNECTIONS[i]); i++)
		addLink (g, CONNECTIONS[i].v, CONNECTIONS[i].w, CONNECTIONS[i].t);
}

#define dprintf(fmt,...) // printf(fmt, __VA_ARGS__)

static int shouldAdd (TransportID type[], int size, TransportID check) {
	for (int i=0; i<size; i++){
		if (check == type[i]) {
			return 0;
		}
	}
	return 1;
}

// Returns the number of direct connections between two nodes
// Also fills the type[] array with the various connection types
// Returns 0 if no direct connection (i.e. not adjacent in graph)
int connections (Map g, LocationID start, LocationID end, TransportID type[])
{
	assert (g != NULL);
	// TODO: complete this fucntion
	assert (validPlace (start) && "Invalid start");
	assert (validPlace (end) && "Invalid end");
	int count = 0;
	VList current = g->connections[start];

	dprintf("End: %s\n", idToName(end));
	// loop through all vertices connected to the starting location
	while (current != NULL) {
		dprintf("loc: %s, type: %s\n", idToName(current->v), transportToName(current->type));
		// a direct connection [rail, road, sea]
		if (current->v == end){
			if (shouldAdd(type, count, current->type)) {
				type[count] = current->type;
				count++;
			}
		}
		// encountered a sea, check if this sea connects to the destination via BOAT
		if (current->type == BOAT){
			// check if its a connection over the sea

			VList sea = g->connections[current->v];
			
			while (sea != NULL){
				if (sea->v == end){
					if (shouldAdd(type, count, current->type)) {
						type[count] = BOAT;
						count++;
						break;
					}
				}
				sea = sea->next;
			}
			
			
		}

		// keep looping
		current = current->next;   
	}
	return count;  // to keep the compiler happy
}
