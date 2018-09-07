#include "linkedList.h"
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

void forEach_LinkedList(LinkedList list, VisitorFn visitorFn) {
  for (LinkedNode *node = list; node != NULL; node = node->next) {
    visitorFn(node->data);
  }
}

void *find_LinkedList(LinkedList list, CompareValueFn compareValueFn, void *value) {
  for (LinkedNode *node = list; node != NULL; node = node->next) {
    if (compareValueFn(node->data, value) == 1) {
      return node->data;
    }
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