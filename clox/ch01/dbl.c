#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct node {
  struct node *prev;
  struct node *next;
  char data[SIZE];
};
typedef struct node * pnode;

pnode create(char d[SIZE]) {
  pnode x = (pnode) malloc(sizeof(struct node));
  strcpy(x->data, d);
  x->prev = NULL;
  x->next = NULL;
  return x;
}

pnode insert(pnode n, char d[SIZE]) {
  pnode x = create(d);
  if(n != NULL){
    if(n->next != NULL){
      x->next = n->next;
      x->next->prev = x;
    }
    n->next = x;
    x->prev = n;
  }
  return x;
}

pnode find(pnode n, char x[SIZE]) {
  if (n == NULL) return NULL;
  int r = strcmp(x, n->data);
  if (!r) return n;
  else return find(n->next, x);
}

pnode delete(pnode n, char x[SIZE]) {
  pnode nx = find(n, x);
  if (nx == NULL) return NULL;
  if (nx->prev != NULL) {
    nx->prev->next = nx->next;
  }
  if (nx->next != NULL) {
    nx->next->prev = nx->prev;
  }
  return nx;
}

void walk(pnode n) {
  if (n == NULL) return;
  printf("%s\n", n->data);
  walk(n->next);
}
void rwalk(pnode n) {
  if (n == NULL) return;
  printf("\t%s\n", n->data);
  rwalk(n->prev);
}

void main() {
  pnode head = insert(NULL, "hello");
  pnode tail = insert(head, "world");
  tail = insert(tail, "!");
  walk(head);
  rwalk(tail);
  delete(head, "world");
  walk(head);
  head = find(head, "!");
  rwalk(head);
}
