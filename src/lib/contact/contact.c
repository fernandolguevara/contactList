#include "contact.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Contact new_Contact() {
  Contact contact = malloc(sizeof(ContactNode));

  contact->firstName  = NULL;
  contact->lastName   = NULL;
  contact->age        = 0;
  contact->gender     = NULL;
  contact->phone      = NULL;
  contact->email      = NULL;
  contact->birthday   = NULL;

  return contact;
}

void free_Contact(Contact contact) {
  free(contact->firstName);
  free(contact->lastName);
  free(contact->firstName);
  free(contact->gender);
  free(contact->phone);
  free(contact->email);
  free(contact->birthday);
  free(contact);
}

void print_Contact(Contact contact) {
  printf("First name: %s\nLast name: %s\nAge: %d\nGender: %s\nPhone: %s\nEmail: %s\nBirthday: %s\n", contact->firstName, contact->lastName, contact->age, contact->gender, contact->phone, contact->email, contact->birthday);
}

int compare_ContactPhoneByValue(Contact contact, char *value) {
  return strcmp(contact->phone, value);
}
