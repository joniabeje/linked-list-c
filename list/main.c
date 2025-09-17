// list/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void) {
  printf("Write your Tests for your linked list implementation\n");

  list_t *mylist = list_alloc();
  list_print(mylist);

  /* build: push to front */
  list_add_to_front(mylist, 10);
  list_add_to_front(mylist, 20);
  list_add_to_front(mylist, 30);
  list_print(mylist);

  /* fill up to match expected string in your tests */
  list_add_to_front(mylist, 40);
  list_add_to_front(mylist, 50);
  list_add_to_front(mylist, 60);
  list_add_to_front(mylist, 70);
  list_add_to_front(mylist, 80);
  list_add_to_front(mylist, 90);
  list_add_to_front(mylist, 100);

  char *s1 = listToString(mylist);
  if (strcmp("100->90->80->70->60->50->40->30->20->10->NULL", s1) != 0) {
    printf("list_add_to_front : FAILED\n");
  }
  free(s1);

  list_print(mylist);
  list_remove_at_index(mylist, 3);
  list_print(mylist);

  char *s2 = listToString(mylist);
  if (strcmp("100->90->70->60->50->40->30->20->10->NULL", s2) != 0) {
    printf("list_remove_at_index : FAILED\n");
  }
  free(s2);

  list_remove_at_index(mylist, 20);
  list_print(mylist);
  list_remove_at_index(mylist, 1);
  list_print(mylist);
  list_remove_at_index(mylist, 6);
  list_print(mylist);

  char *s3 = listToString(mylist);
  if (strcmp("90->70->60->50->40->20->10->NULL", s3) != 0) {
    printf("list_remove_at_index : FAILED\n");
  }
  free(s3);

  /* getters */
  printf("Value at %d in the list?: %d\n", 3, list_get_elem_at(mylist, 3));
  printf("Value at %d in the list?: %d\n", 5, list_get_elem_at(mylist, 5));
  printf("Value at %d in the list?: %d\n", 0, list_get_elem_at(mylist, 0));
  printf("Value at %d in the list?: %d\n", -2, list_get_elem_at(mylist, -2));
  printf("Value at %d in the list?: %d\n", 12, list_get_elem_at(mylist, 12));
  printf("Value at %d in the list?: %d\n", 7, list_get_elem_at(mylist, 7));

  printf("Index of %d?: %d\n", 70, list_get_index_of(mylist, 70));
  printf("Index of %d?: %d\n", 20, list_get_index_of(mylist, 20));
  printf("Index of %d?: %d\n", 0,  list_get_index_of(mylist, 0));
  printf("Index of %d?: %d\n", 10, list_get_index_of(mylist, 10));
  printf("Index of %d?: %d\n", 90, list_get_index_of(mylist, 90));

  list_free(mylist);
  return 0;
}
