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

typedef struct {
  Node *head;
  Node *tail;
  int count;
  int sizeof_data;
} List;

static List *list_new(const int sizeof_data) {
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
  list->tail = current->previous;
  current->previous->next = NULL;
  free(current);
  return data;
}
static void free_list(List *list) {
  int i = 0;
  while (list->count > 0) {
    void *element = pop(list);
    free(element);
    i++;
  }
  assert(list->count == 0);
  free(list);
  list = NULL;
}
static Node *node_at(List *list, int index) {
  if (index == 0) {
    assert(list->head != NULL);
    return list->head;
  }
  if (index == list->count - 1) {
    assert(list->tail != NULL);
    return list->tail;
  }
  
  int current;
  Node *node = NULL;
  
  if (index > list->count / 2) {
    // closer to the end
    node = list->tail;
    for (current = list->count - 1; current > index && current > 0; --current) {
      node = node->previous;
    }
  } else {
    // closer to the beginning
    node = list->head;
    for (current = 0; current < index && current < list->count; ++current) {
      node = node->next;
    }
  }
  assert(current == index);
  assert(node != NULL);
  return node;
}
static void *at(List *list, const int index) {
  return node_at(list, index)->data;
}
static void insert(List *list, const int index, void *data) {
  assert(index <= list->count);
  // if index is count, which is out of bounds, we just push back.
  if (index == list->count) {
    push(list, data);
    return;
  }
  
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;

  if (index == 0) {
    // if at index 0, we don't need to setup the previous node.
    // ?? -> current -> ??
    Node *current = list->head;
    // new_node <- current
    current->previous = new_node;
    // new_node -> current
    new_node->next = current;
    // establish new head of list.
    list->head = new_node;
  
  } else {
    Node *previous = node_at(list, index - 1);
    Node *current = previous->next;
    
    previous->next = new_node;
    
    if (current != NULL)
        current->previous = new_node;
    
    new_node->previous = previous;
    new_node->next = current;
  }
  list->count++;
}
#endif
