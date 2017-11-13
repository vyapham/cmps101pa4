#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
  FILE *in, *out;
  int n = 0;
  
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  
  in = fopen(argv[1], "r");
  
  if(in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  
  out = fopen(argv[2], "w");
  
  if(out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  
  fscanf(in, "%d", &n);
  Graph G = newGraph(n);
  int v1 = 0;
  int v2 = 0;
	
  while(fgetc(in) != EOF)  {
    fscanf(in, "%d", &v1);
    fscanf(in, "%d", &v2);     
    if (v1 == 0 && v2 == 0) {
      break;
    }
    addEdge(G, v1, v2);
    
  }
  
  printGraph(out, G);
  fprintf(out, "\n");
  
  while (fgetc(in) != EOF) {
    fscanf(in, "%d", &v1);
    fscanf(in, "%d", &v2);     
    if (v1 == 0 && v2 == 0) {
      break;
    }
    // v1 is the starting point, v2 is the destination
    BFS(G, v1);
    List L = newList();
    getPath(L, G, v2);
    if (getDist(G, v2) == INF) {
      fprintf(out, "The distance from %d to %d is infinity\n", v1, v2);
      fprintf(out, "No %d-%d path exists\n", v1, v2);
    }
    else {
      fprintf(out, "The distance from %d to %d is %d\n", v1, v2, getDist(G, v2));
      fprintf(out, "A shortest %d-%d path is: ", v1, v2);
      printList(out, L);
      fprintf(out, "\n");
    }
    fprintf(out, "\n");
    freeList(&L);
  }
  
  fclose(in);
  fclose(out);
  
  freeGraph(&G);
  
  return 0;
  
}
