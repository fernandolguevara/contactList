#include "linkedList.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

LinkedList new_LinkedList() {
  return NULL;
}

void free_LinkedList(LinkedList list) {
  LinkedNode *deleteNode;

  while (list != NULL) {
    deleteNode = list;
    list = list->next;
    free(deleteNode);
  }
}

int isEmpty_LinkedList(LinkedList list) {
  return list == NULL;
}

LinkedList push_LinkedList(LinkedList list, void *data) {
  LinkedNode *newNode = malloc(sizeof(LinkedNode));

  newNode->data = data;
  newNode->next = NULL;

  if (list == NULL) {
    return newNode;
  }

  LinkedNode *lastNode = list;
  for (; lastNode->next != NULL; lastNode = lastNode->next);

  lastNode->next = newNode;

  return list;
}

void forEach_LinkedList(LinkedList list, VisitorFn_void visitorFn_void, ...) {
  va_list ap;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    va_start(ap, visitorFn_void);
    visitorFn_void(node->data, ap);
    va_end(ap);
  }
}

void *find_LinkedList(LinkedList list, VisitorFn_int visitorFn_int, ...) {
  va_list ap;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    va_start(ap, visitorFn_int);
    if (visitorFn_int(node->data, ap)) {
      va_end(ap);
      return node->data;
    }
    va_end(ap);
  }

  return NULL;
}

void *delete_LinkedList(LinkedList list, void *data) {
  LinkedNode *node = list, *prev;

  if (node != NULL && node->data == data) {
    list = node->next;
    free(node);
  } else {
    while (node != NULL && node->data != data) {
        prev = node;
        node = node->next;
    }
 
    if (node != NULL) {
      prev->next = node->next;
      free(node);  
    }
  }
  
  return list;
}

int length_LinkedList(LinkedList list) {
  int x = 0;

  for (LinkedNode *node = list; node != NULL; node = node->next, x++);

  return x;
}