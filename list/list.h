// list/list.h
//
// Interface definition for linked list.

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

/* element type for the list */
typedef int elem;

/* node and list types */
typedef struct node {
  elem value;
  struct node *next;
} node_t;

typedef struct list {
  node_t *head;
} list_t;

/* allocation / teardown */
list_t *list_alloc(void);
void     list_free(list_t *l);

/* debug helpers */
void     list_print(list_t *l);
char    *listToString(list_t *l);

/* utility to create a node on the heap (kept for your tests) */
node_t  *getNode(elem value);

/* length */
int      list_length(list_t *l);

/* add */
void     list_add_to_back(list_t *l, elem value);
void     list_add_to_front(list_t *l, elem value);
void     list_add_at_index(list_t *l, elem value, int index);  // 1-based index

/* remove (returns removed elem or -1 on error) */
elem     list_remove_from_back(list_t *l);
elem     list_remove_from_front(list_t *l);
elem     list_remove_at_index(list_t *l, int index);           // 1-based index

/* queries */
bool     list_is_in(list_t *l, elem value);
elem     list_get_elem_at(list_t *l, int index);               // 1-based index; -1 on error
int      list_get_index_of(list_t *l, elem value);             // 1-based index; -1 if absent

#endif
