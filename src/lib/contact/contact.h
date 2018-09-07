#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct _ContactNode {
  char *firstName;
  char *lastName;
  int age;
  char *gender;
  char *phone;
  char *email;
  char *birthday;
} ContactNode;

typedef ContactNode *Contact;

/**
 * Creates a Contact.
 */
Contact new_Contact();

/**
 * Frees the Contact.
 */
void free_Contact(Contact contact);

/**
 * Prints the Contact.
 */
void print_Contact(Contact contact);

/**
 * Compares the contact phone with a value.
 */
int compare_ContactPhoneByValue(Contact contact, char *value);

#endif /* __CONTACT_H__ */
