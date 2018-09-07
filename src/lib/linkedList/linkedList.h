#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include <stdio.h>

typedef void (*VisitorFn) (void *data);
typedef int (*CompareValueFn) (void *data, void *value);

typedef struct _LinkedNode {
  void *data;
  struct _LinkedNode *next;
} LinkedNode;

typedef LinkedNode *LinkedList;

/**
 * Creates a new LinkedList.
 */
LinkedList new_LinkedList();

/**
 * Frees the LinkedList.
 */
void free_LinkedList(LinkedList list);

/**
 * Returns if the LinkedList is empty.
 */
int isEmpty_LinkedList(LinkedList list);

/**
 * Adds an element to the end of the LinkedList.
 */
LinkedList push_LinkedList(LinkedList list, void *data);

/**
 * Executes a function for each element in the LinkedList.
 */
void forEach_LinkedList(LinkedList list, VisitorFn visitorFn);

/**
 * Fin an element in the list where the compare value fn returns true. 
 */
void *find_LinkedList(LinkedList list, CompareValueFn compareValueFn, void *value);

/**
 * Delete an element of the list.
 */
void *delete_LinkedList(LinkedList list, void *data);

/**
 * Returns the length of the LinkedList.
 */
int length_LinkedList(LinkedList list);

#endif /* __LINKED_LIST_H__ */
