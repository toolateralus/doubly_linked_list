#include "list.h"
#include <stdio.h>


typedef struct {
  int a, b;
  char c;
} test_t;

test_t *make_test_struct(int a, int b, char c) {
  test_t *test = (test_t*)malloc(sizeof(test_t));
  test->a = a;
  test->b = b;
  test->c = c;
  return test;
}
void mass_test() {
  
  char input = 0;
  
  printf("examine memory usage, then type '1' then press enter to fill & empty the list.\n");
  
  while (1) {
    scanf("%c", &input);
    
    if (input) {
      break;
    }
  }
  
  List *list = list_new(sizeof(test_t));
  for (int i = 0; i < 25; ++i) {
     push(list, make_test_struct(i, i * 2, i % 255));
  }
  printf("\nsizeof list: %d\n", list->count);
  
  int i = 0;
  while (list->count > 0) {
    test_t *element = pop(list);
    printf("%d, %d, %c\n", element->a, element->b, element->c);
    free(element);
    i++;
  }
  
  printf("list destroyed : %d elements\n", i);
  
  free(list);
  
  printf("examine memory usage, or type '1' and press enter to exit.\n");
  
  input = 0;
  
  while(1) {
    scanf(" %c", &input);
    if (input != 0) {
      break;
    }
  }
}

int main(int argc, char **argv) {
  mass_test();
  return 0;
}

