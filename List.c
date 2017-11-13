/*********
 * Name: VY PHAM
 * ID: vyapham
 * Student ID #: 1593394
 * Assignment name: pa4
 ********/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj {
  int data;
  struct NodeObj* next;
  struct NodeObj* previous;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

Node newNode(int data) {
  Node N = malloc(sizeof(NodeObj));
  N -> data = data;
  N -> next = NULL;
  N -> previous = NULL;
  return(N);
}

void freeNode(Node* pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Constructors - Destructors

List newList(void) {
  List L = NULL;
  L = malloc(sizeof(ListObj));
  L -> front = NULL;
  L -> back = NULL;
  L -> cursor = NULL;
  L -> length = 0;
  L -> index = -1;
  return(L);
}

int isEmpty(List L) {
  if (L == NULL) {
    printf("isEmpty() is called on NULL List reference\n");
    exit(1);
  }
  return (L -> length == 0);
}

void freeList(List* pL) {
  if (pL != NULL && *pL != NULL) {
    while (!isEmpty(*pL)) {
        deleteFront(*pL);
      }	
    free(*pL);
    *pL = NULL;
  }
}

// Access functions----------------

int length(List L) {
  if (L == NULL) {
    printf("NULL list reference\n");
    exit(1);
  }
  return L -> length;
}

int index(List L) {
  if (L == NULL) {
    printf("NULL list reference\n");
    exit(1);
  }
  if (L -> cursor == NULL) {
    return -1;
  }
  else {
    return L -> index;
  }
}

int front(List L) {
  if (L == NULL) {
    printf("NULL list reference\n");
    exit(1);
  }
  if (length(L) != 0) {
    return L -> front -> data;
  }
  else {
    printf("List is empty\n");
    exit(1);
  }
}

int back(List L) {
  if (L == NULL) {
    printf("NULL list reference\n");
    exit(1);
  }
  if (length(L) != 0) {
    return L -> back -> data;
  }
  else {
    printf("List is empty\n");
    exit(1);
  }
}

int get(List L) {
  if (L == NULL) {
    printf("NULL list reference\n");
    exit(1);
  }
  if (length(L) <= 0) {
    printf("List is empty\n");
    exit(1);
  }
  if (index(L) < 0) {
    printf("index < 0\n");
    exit(1);
  }
  return L->cursor->data;
}

int equals(List A, List B) {
  int eq = 0;
  Node N = NULL;
  Node M = NULL;

  if (A == NULL || B == NULL) {
    printf("NULL List reference");
    exit(1);
  }

  eq = (A -> length == B -> length);
  N = A -> front;
  M = B -> front;
  while (eq && N != NULL) {
    eq = (N -> data == M -> data);
    N = N -> next;
    M = M -> next;
  }
  
  //  freeNode(&N);
  //  freeNode(&M);

  return eq;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
  while (L -> front != NULL) {
    deleteBack(L);
  }
  L -> front = L -> back = L -> cursor = NULL;
  L -> length = 0;
  L -> index = -1;
}

void moveFront(List L) {
  if (length(L) > 0) {
    L -> cursor = L -> front;
    L -> index = 0;
  }
}

void moveBack(List L) {
  if (length(L) > 0) {
    L -> cursor = L -> back;
    L -> index = length(L) - 1;
  }
}

void movePrev(List L) {
  if (L -> cursor != NULL) {
    if (L -> cursor != L -> front) {
      L -> cursor = L -> cursor -> previous;
      L -> index--;
    }
    else {
      L -> cursor = NULL;
      L -> index = -1;
    }
  }
}

void moveNext(List L) {
  if (L -> cursor != NULL) {
    if (L -> cursor != L -> back) {
      L -> cursor = L -> cursor -> next;
      L -> index++;    
    }
    else {
      L -> cursor = NULL;
      L -> index = -1;
    }
  }
}

void prepend(List L, int data) {
  Node N = newNode(data);
  if (length(L) == 0) {
    L -> front = L -> back = N;
  }
  else {
    N -> next = L -> front;
    L -> front -> previous = N;
    L -> front = N;
  }
  L -> length++;
  if (L -> cursor != NULL) {
    L -> index++;
  }
}

void append(List L, int data) {
  Node N = newNode(data); 
  if (length(L) == 0) {
    L -> front = L -> back = N;
  }
  else {
    N -> previous = L -> back;
    L -> back -> next = N;
    L -> back = N;
  }
  L -> length++;
}

void insertBefore(List L, int data) {
  if (length(L) > 0 && index(L) >= 0) {
    Node N = newNode(data);
    if (index(L) > 0) {
      N -> next = L -> cursor;
      N -> previous = L -> cursor -> previous;
      L -> cursor -> previous -> next = N;
      L -> cursor -> previous = N;
    }
    else {
      N -> next = L -> front;
      L -> front -> previous = N;
      L -> front = N;
    }
    L -> length++;
    if(L -> cursor != NULL) {
      L -> index++;
    }
  }
}

void insertAfter(List L, int data) {
  if (length(L) > 0 && index(L) >= 0) {
    Node N = newNode(data);
    if (index(L) != length(L) - 1) {
      N -> next = L -> cursor -> next;
      N -> previous = L -> cursor;
      L -> cursor -> next -> previous = N;
      L -> cursor -> next = N;
    }
    else {
      N -> previous = L -> back;
      L -> back -> next = N;
      L -> back = N;
    }
    L -> length++;
  }
}

void deleteFront(List L) {
  Node N = NULL;
  if (length(L) > 0) {
    N = L -> front;
    if (length(L) > 1) {
      if  (L -> cursor != NULL) {
	if (L -> cursor == L -> front) {
	  L -> cursor = NULL;
	}
	else {
	  L -> index--;
	}
      }
      L -> front = L -> front -> next;
      L -> front -> previous = NULL;
    }
    else {
      L -> front = L -> back = NULL;
      if (L -> cursor != NULL) {
	L -> cursor = NULL;
      }
    }
    L -> length--;
  }
  freeNode(&N);
}

void deleteBack(List L) {
  Node N = NULL;
  if (length(L) > 0) {
    N = L -> back;
    if (length(L) > 1) {
      if (L -> cursor != NULL) {
	if (L -> cursor == L -> back) {
	  L -> cursor = NULL;
	}
	else {
	  // do nothing
	}
      }
      L -> back = L -> back -> previous;
      L -> back -> next = NULL;
    }
    else {
      L -> front = L -> back = NULL;
      if (L -> cursor != NULL) {
	L -> cursor = NULL;
      }
    }
    L -> length--;
  }
  freeNode(&N);
}

void delete(List L) {
  if (length(L) > 0 && index(L) >= 0) {
    Node N = NULL;
    if (length(L) == 1) {
      N = L -> cursor;
      L -> front = L -> back = L -> cursor = NULL;
    }
    else {
      if (L -> cursor == L -> front) {
	N = L -> cursor;
	L -> front = L -> front -> next;
	L -> front -> previous = NULL;
	N -> next = NULL;
	L -> cursor = NULL;
      }
      else if (L -> cursor == L -> back) {
	N = L -> cursor;
	L -> back = L -> back -> previous;
	L -> back -> next = NULL;
	N -> previous = NULL;
	L -> cursor = NULL;
      }
      else {
	N = L -> cursor;
	L -> cursor -> next -> previous = L -> cursor -> previous;
	L -> cursor -> previous -> next = L -> cursor -> next;
	N -> next = NULL;
        N -> previous = NULL;
	L -> cursor = NULL;
      }
    }
    L -> length--;
    freeNode(&N);
  }
}

// Other operations ----------------------------
void printList(FILE* out, List L){
  if (L == NULL) {
    printf("NULL List referrence\n");
    exit(1);
  }
  Node N = L -> front;
  while (N != NULL) {
    fprintf(out, "%d ", N -> data);
    N = N -> next;
  }
}

List copyList(List L) {
  List newL = newList();
  Node N = L -> front;
  while (N != NULL) {
    append(newL, N -> data);
    N = N -> next;
  }
  return newL;
}
