#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

typedef struct _LinkedNode {
  void *data;
  struct _LinkedNode *next;
} LinkedNode;

typedef LinkedNode *LinkedList;
typedef void (*VisitorFn_void) (void *data, va_list ap);
typedef int (*VisitorFn_int) (void *data, va_list ap);
typedef int (*CompareFn) (void *a, void *b, va_list ap);

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
void forEach_LinkedList(LinkedList list, VisitorFn_void visitorFn_void, ...);

/**
 * Find an element that pass the VisitorFn_int. 
 */
void *find_LinkedList(LinkedList list, VisitorFn_int visitorFn_int, ...);

/**
 * Delete an element of the list.
 */
void *delete_LinkedList(LinkedList list, void *data);

/**
 * Returns the length of the LinkedList.
 */
int length_LinkedList(LinkedList list);

/**
 * Sorts the LinkedList by the CompareFn.
 */
void bubbleSort_LinkedList(LinkedList list, CompareFn compareFn, ...);

#endif /* __LINKED_LIST_H__ */
