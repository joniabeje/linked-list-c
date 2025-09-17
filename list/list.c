// list/list.c
//
// Implementation for linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/* internal helper */
static node_t *node_new(elem value) {
  node_t *n = (node_t *)malloc(sizeof(node_t));
  if (!n) { fprintf(stderr, "malloc failed\n"); exit(1); }
  n->value = value;
  n->next  = NULL;
  return n;
}

/* public wrapper kept for your header/tests */
node_t *getNode(elem value) { return node_new(value); }

list_t *list_alloc(void) {
  list_t *mylist = (list_t *)malloc(sizeof(list_t));
  if (!mylist) { fprintf(stderr, "malloc failed\n"); exit(1); }
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  if (!l) return;
  node_t *c = l->head;
  while (c) {
    node_t *next = c->next;
    free(c);
    c = next;
  }
  free(l);
}

void list_print(list_t *l) {
  if (!l || !l->head) { printf("NULL\n"); return; }
  for (node_t *c = l->head; c; c = c->next) printf("%d->", c->value);
  printf("NULL\n");
}

char *listToString(list_t *l) {
  if (!l || !l->head) {
    char *s = (char *)malloc(5);
    strcpy(s, "NULL");
    return s;
  }
  char *buf = (char *)malloc(10024);
  if (!buf) { fprintf(stderr, "malloc failed\n"); exit(1); }
  buf[0] = '\0';

  char tbuf[32];
  for (node_t *c = l->head; c; c = c->next) {
    snprintf(tbuf, sizeof(tbuf), "%d->", c->value);
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int count = 0;
  for (node_t *c = l ? l->head : NULL; c; c = c->next) count++;
  return count;
}

void list_add_to_front(list_t *l, elem value) {
  node_t *n = node_new(value);
  n->next = l->head;
  l->head = n;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *n = node_new(value);
  if (!l->head) { l->head = n; return; }
  node_t *c = l->head;
  while (c->next) c = c->next;
  c->next = n;
}

/* ---------- 1-based indexing; out-of-range => NO-OP ---------- */
void list_add_at_index(list_t *l, elem value, int index) {
  if (!l || index <= 0) return;

  if (index == 1) { list_add_to_front(l, value); return; }
  if (!l->head) return;  // index>1 but empty -> no-op

  // walk to node at position (index-1); if absent, no-op
  node_t *prev = l->head;
  int pos = 1;
  while (prev && pos < index - 1) { prev = prev->next; pos++; }
  if (!prev) return;   // index beyond length -> no-op

  node_t *n = node_new(value);
  n->next = prev->next;   // inserts in middle or at tail when index == length+1
  prev->next = n;
}

elem list_remove_from_front(list_t *l) {
  if (!l || !l->head) return -1;
  node_t *del = l->head;
  elem v = del->value;
  l->head = del->next;
  free(del);
  return v;
}

elem list_remove_from_back(list_t *l) {
  if (!l || !l->head) return -1;
  if (!l->head->next) return list_remove_from_front(l);

  node_t *prev = l->head;
  node_t *curr = l->head->next;
  while (curr->next) { prev = curr; curr = curr->next; }
  elem v = curr->value;
  prev->next = NULL;
  free(curr);
  return v;
}

/* ---------- 1-based indexing; out-of-range => -1 (no change) ---------- */
elem list_remove_at_index(list_t *l, int index) {
  if (!l || index <= 0 || !l->head) return -1;
  if (index == 1) return list_remove_from_front(l);

  node_t *prev = l->head;
  int pos = 1;
  while (prev && pos < index - 1) { prev = prev->next; pos++; }
  if (!prev || !prev->next) return -1;  // out of range

  node_t *del = prev->next;
  elem v = del->value;
  prev->next = del->next;
  free(del);
  return v;
}

bool list_is_in(list_t *l, elem value) {
  for (node_t *c = l ? l->head : NULL; c; c = c->next)
    if (c->value == value) return true;
  return false;
}

/* keep your getters 1-based like your main expects */
elem list_get_elem_at(list_t *l, int index) {
  if (!l || index <= 0) return -1;
  node_t *c = l->head; int pos = 1;
  while (c && pos < index) { c = c->next; pos++; }
  return c ? c->value : -1;
}

int list_get_index_of(list_t *l, elem value) {
  int pos = 1;
  for (node_t *c = l ? l->head : NULL; c; c = c->next, pos++)
    if (c->value == value) return pos;
  return -1;
}
