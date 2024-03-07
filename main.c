#include "list.h"
#include <stdio.h>

typedef struct {
  int a, b, c;
} test_t;
test_t *make_test_struct(int a, int b, int c) {
  test_t *test = (test_t *)malloc(sizeof(test_t));
  test->a = a;
  test->b = b;
  test->c = c;
  return test;
}
void test_push_pop() {
  
  char input = 0;
  printf("MASS_PUSH_MASS_POP_TEST\n");
    
  List *list = list_new(sizeof(test_t));
  for (int i = 0; i < 25; ++i) {
    push(list, make_test_struct(i, i * 2, i % 255));
  }
  //printf("\nsizeof list: %d\n", list->count);
  
  int i = 0;
  while (list->count > 0) {
    test_t *element = pop(list);
    //printf("%d, %d, %c\n", element->a, element->b, element->c);
    free(element);
    i++;
  }
  
  //printf("list destroyed : %d elements\n", i);
  
  free(list);
  printf("MASS_PUSH_MASS_POP PASSED\n");
}
void test_element_at() {
  printf("INDEXING_'at()'_TEST\n");
  
  List *list = list_new(sizeof(test_t));
  
  for (int i = 0; i < 250; ++i) {
    push(list, make_test_struct(i,i,i));
  }
  
  for (int i = 0; i < 250; ++i) {
    test_t *element = at(list, i);
    if (element == NULL) {
      printf("fetched element at index %d was null\n", i);
      return;
    }
    printf("i==%d\n",i);
    assert(element->a == i);
    assert(element->b == i);
    assert(element->c == i);
  }
  printf("INDEXEX_'at()'_TEST PASSED\n");
}
void test_insertion(const int insertion_index, const char* title) {
  printf("INSERTION_TEST_AT_%s\n", title);
  
  List *list = list_new(sizeof(test_t));
  for (int i = 0; i < 2500; ++i) {
    push(list, make_test_struct(0, 0, 0));
  }
  
  const int desired_size = list->count + 1;
  
  const int test_value_a = 10;
  const int test_value_b = 11;
  const char test_value_c = 12;
  
  const test_t *test_struct = make_test_struct(test_value_a, test_value_b, test_value_c);
  
  insert(list, insertion_index, (void*)test_struct);
  
  assert(list->count == desired_size);
  
  const test_t *element = at(list, insertion_index);
  
  assert(element->a == test_value_a);
  assert(element->b == test_value_b);
  assert(element->c == test_value_c);
  
}
enum INSERTION_TEST {
  INSERT_AT_HEAD = 0,
  INSERT_IN_MIDDLE = 1,
  INSERT_AT_TAIL = 5,
};
void test_freeing_list() {
  printf("TEST_FREE_LIST\n");
  List *list = list_new(sizeof(test_t));
  for (int i = 0; i < 250; ++i) {
    push(list, make_test_struct(0,0,0));
  }
  free_list(list);
  assert(list->count == 0);
  list = NULL;
  printf("TEST_FREE_LIST PASSED\n");
}
void test_insert_at_one() {
  List *list = list_new(sizeof(test_t));
  
  for (int i = 0 ; i < 10; ++i) {
    push(list, make_test_struct(i, i, i % 255));
  }
  
  test_t *test = make_test_struct(100, 100, 100);
  
  insert(list, 1, test);
  
  test_t *t1 = at(list, 1);
  test_t *t2 = at(list, 2);
  
  printf("at index 1 %d,%d,%d\n", t1->a, t1->b, t1->c);
  printf("at index 2 %d,%d,%d\n", t2->a, t2->b, t2->c);
}

void test_insert_at_1251() {
  List *list = list_new(sizeof(test_t));
  
  for (int i = 0 ; i < 2500; ++i) {
    push(list, make_test_struct(i, i, i % 255));
  }
  
  test_t *test = make_test_struct(100, 100, 100);
  
  insert(list, 1251, test);
  
  test_t *t1 = at(list, 1251);
  test_t *t2 = at(list, 1252);
  
  printf("at index 1251 %d,%d,%d\n", t1->a, t1->b, t1->c);
  printf("at index 1252 %d,%d,%d\n", t2->a, t2->b, t2->c);
}

int main(int argc, char **argv) {
  test_push_pop();
  test_element_at();
  test_freeing_list();
  test_insert_at_one();
  test_insert_at_1251();
  test_insertion(0, "HEAD");
  test_insertion(1, "ONE");
  test_insertion(2, "TAIL");
  
   for (int i = 0; i < 2500; ++i) {
     printf("%d\n", i);
     test_insertion(i, "LOOP");
   }
  return 0;
}
