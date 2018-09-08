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
typedef int (*Compare_ContactFn) (Contact a, Contact b);

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

/**
 * Writes the Contact in a file.
 */
void writeInFile_Contact(Contact contact, FILE *f);

/**
 * Compares two Contacts by firstName.
 */
int compareByFirstName_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by lastName.
 */
int compareByLastName_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by age.
 */
int compareByAge_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by gender.
 */
int compareByGender_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by phone.
 */
int compareByPhone_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by email.
 */
int compareByEmail_Contact(Contact a, Contact b);

/**
 * Compares two Contacts by birthday.
 */
int compareByBirthday_Contact(Contact a, Contact b);

#endif /* __CONTACT_H__ */
