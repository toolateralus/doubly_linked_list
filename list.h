#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef LIST_H

#else
#define LIST_H

typedef struct node_t {
  struct node_t *next;
  struct node_t *previous;
  void *data;
} Node;

typedef struct list_t {
  Node *head;
  Node *tail;
  int count;
  int sizeof_data;
} List;

static List *list_new(int sizeof_data) {
  assert(sizeof_data != 0);
  List *list = (List *)malloc(sizeof(List));
  list->sizeof_data = sizeof_data;
  list->count = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

static void push(List *list, void *data) {
  assert(list != NULL);
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    Node *tail = list->tail;
    tail->next = node;
    node->previous = tail;
    list->tail = node;
  }
  list->count++;
}

static void *pop(List *list) {
  assert(list != NULL);
  assert(list->count > 0);
  assert(list->head != NULL);

  Node *current = list->tail;
  
  int count = list->count;
  
  list->count--;
  
  if (count == 1) {
    void *data = current->data;
    free(current);
    list->head = NULL;
    return data;
  }
  
  void *data = current->data;
  list->tail =current->previous;
  current->previous->next = NULL;
  free(current);
  return data;
}

#endif