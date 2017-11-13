/*********
 * Name: VY PHAM
 * ID: vyapham
 * Student ID #: 1593394
 * Assignment name: pa4
 ********/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
	List* L;		// contains neighbors of vertex i
	int* color;		// white = 0; gray = 1; black = 2;
	int* parent;	// parents of vertex i
	int* distance;	// distance from the most recent source to vertex i
	int order;		// number of vertices
	int size;		// number of edges
	int source;		// the vertex that was most recently used in BFS
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));

	// Assign length of all arrays n + 1 for easier use
	G -> L = calloc(n + 1, sizeof(List));
	G -> color = calloc(n + 1, sizeof(int));
	G -> parent = calloc(n + 1, sizeof(int));
	G -> distance = calloc(n + 1, sizeof(int));
	
	for (int i = 1; i < n + 1; i++) {
		G -> L[i] = newList();
		G -> color[i] = WHITE;
		G -> parent[i] = NIL;
		G -> distance[i] = INF;
	}
	G -> order = n;
	G -> size = 0;
	G -> source = NIL;

	return G;
}

void freeGraph(Graph* pG) {
        for (int i = 1; i < getOrder(*pG); i++) {
		freeList(&(*pG) -> L[i]);
	}
	free((*pG) -> L);
	free((*pG) -> color);
	free((*pG) -> parent);
	free((*pG) -> distance);
	free(*pG);
	//*pG = NULL;
	return;
}

/*** Access functions ***/
int getOrder(Graph G) {
	return G -> order;
}

int getSize(Graph G) {
	return G -> size;
}

int getSource(Graph G) {
	return G -> source;
}

int getParent(Graph G, int u) {
	if (!(1 <= u && u <= getOrder(G))) {
		printf("Error: getParent() called on invalid vertex");
		exit(1);
	}
	return G -> parent[u];
}

int getDist(Graph G, int u) {
	if (!(1 <= u && u <= getOrder(G))) {
		printf("Error: getDist() called on invalid vertex");
		exit(1);
	}	
	return G -> distance[u];
}

void getPath(List L, Graph G, int u) {
	if (!(1 <= u && u <= getOrder(G))) {
		printf("Error: getPath() called on invalid vertex");
		exit(1);
	}
	if (getSource(G) == NIL) {
		exit(1);
	}
	if (getSource(G) == u) {
		append(L, getSource(G));
		return;
	}
	if (G -> parent[u] == NIL) {
		append(L, NIL);
		return;
	}
	getPath(L, G, G -> parent[u]);
	append(L, u);
	return;
}

/*** Manipulation procedures ***/
void makeNull(Graph G) {
	for (int i = 1; i < getOrder(G) + 1; i++) {
		clear(G -> L[i]);
		//G -> color[i] = WHITE;
		//G -> parent[i] = NIL;
		//G -> distance[i] = INF;
	}
	G -> size = 0;
	//G -> source = NIL;

	return;
}

void insertion(List L, int n) {
	if (length(L) == 0) {
		append(L, n);
		return;
	}
	if (front(L) > n) {
		prepend(L, n);
		return;
	}
	if (back(L) < n) {
		append(L, n);
		return;
	}
	moveFront(L);
	while (index(L) != -1) {
		if (n >= get(L)) {
			moveNext(L);
		}
		else {
			insertBefore(L, n);
			break;
		}
	}
	return;
}

void addEdge(Graph G, int u, int v) {
	if (!(1 <= u && u <= getOrder(G)) || !(1 <= v && v <= getOrder(G))) {
		printf("Error: addEdge() called on invalid vertex number");
		exit(1);
	}
	insertion(G -> L[u], v);
	insertion(G -> L[v], u);
	G -> size ++;
	return;
}

void addArc(Graph G, int u, int v) {
	if (!(1 <= u && u <= getOrder(G)) || !(1 <= v && v <= getOrder(G))) {
		printf("Error: addArc() called on invalid vertex number");
		exit(1);
	}
	insertion(G -> L[u], v);
	G -> size ++;
	return;
}

void BFS(Graph G, int s) {
	for (int i = 1; i < getOrder(G) + 1; i++) {
		G -> color[i] = WHITE;
		G -> distance[i] = INF;
		G -> parent[i] = NIL;
	}
	G -> source = s;
	G -> color[s] = GRAY;
	G -> distance[s] = 0;
	G -> parent[s] = NIL;
	List Q = newList();	        // Use this as a queue, no need to modify List ADT
	append(Q, s);		// ~ Enqueue
	while (length(Q) != 0) {
		int x = front(Q);
		deleteFront(Q); // ~ Dequeue
		moveFront(G -> L[x]);
		while (index(G -> L[x]) != -1) {
			if (G -> color[get(G -> L[x])] == WHITE) {
				G -> color[get(G -> L[x])] = GRAY;
				G -> distance[get(G -> L[x])] = G -> distance[x] + 1;
				G -> parent[get(G -> L[x])] = x;
				append(Q, get(G -> L[x]));
			}
			moveNext(G -> L[x]);
			}
		G -> color[x] = BLACK;	
	}
	freeList(&Q);
	return;
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	for (int i = 1; i < getOrder(G) + 1; i++) {
		fprintf(out, "%i: ", i);
		printList(out, G -> L[i]);
		fprintf(out, "\n");
	}
	return;
}
