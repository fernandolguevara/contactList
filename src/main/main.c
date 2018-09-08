#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedList/linkedList.h"
#include "../lib/contact/contact.h"

/**
 * WRAPPERS
 * To connect Contact with LinkeList.
 **/

void print_Contact_wrapper(void *data, va_list ap) {
  Contact contact = (Contact)data;

  print_Contact(contact);
  printf("______________________________________________\n");
}

void free_Contact_wrapper(void *data, va_list ap) {
  Contact contact = (Contact)data;

  free_Contact(contact);
}

int compare_ContactPhoneByValue_wrapper(void *data, va_list ap) {
  Contact contact = (Contact)data;
  char* phone = va_arg(ap, char*);

  return compare_ContactPhoneByValue(contact, phone) == 0;
}

void writeInFile_Contact_wrapper(void *data, va_list ap) {
  Contact contact = (Contact)data;
  FILE *f = va_arg(ap, FILE*);

  fprintf(f, "%s\n%s\n%d\n%s\n%s\n%s\n%s\n", contact->firstName, contact->lastName, contact->age, contact->gender, contact->phone, contact->email, contact->birthday);
}

/**
 * UTIL
 * Some utilities.
 **/

float averageAge_Contacts (LinkedList list) {
  // I wanted to declare a reduceToInt_LinkedList function
  int sum = 0;
  Contact contact;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    contact = (Contact)(node->data);
    sum += contact->age;
  }

  /** I could calculate the length above but I like to module all the function
   * in cases where optimization is not needed.
   **/
  return ((float)sum)/length_LinkedList(list);
}

// I want to control the Contact string attributes memory alocation (like in free_Contact).
char *convert_char_array_to_pointer(char array[]) {
  char *pointer = malloc(sizeof(char) * strlen(array));

  strcpy(pointer, array);

  return pointer;
}

/**
 * FILE READ/WRITE
 **/

LinkedList importContacts(LinkedList list) {
  FILE *f = fopen("contacts.txt", "r");
  Contact contact;
  char buffer[50];
  int length;

  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  fscanf(f, "%d", &length);

  for (int x = 0; x < length; x++) {
    contact = new_Contact();

    fscanf(f, "%s", buffer);
    contact->firstName = convert_char_array_to_pointer(buffer);
    fscanf(f, "%s", buffer);
    contact->lastName = convert_char_array_to_pointer(buffer);
    fscanf(f, "%d", &(contact->age));
    fscanf(f, "%s", buffer);
    contact->gender = convert_char_array_to_pointer(buffer);
    fscanf(f, "%s", buffer);
    contact->phone = convert_char_array_to_pointer(buffer);
    fscanf(f, "%s", buffer);
    contact->email = convert_char_array_to_pointer(buffer);
    fscanf(f, "%s", buffer);
    contact->birthday = convert_char_array_to_pointer(buffer);

    list = push_LinkedList(list, contact);
  }

  return list;
}

void exportContacts(LinkedList list) {
  FILE *f = fopen("contacts.txt", "w");
  Contact contact; 

  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  fprintf(f, "%d\n", length_LinkedList(list));

  forEach_LinkedList(list, writeInFile_Contact_wrapper, f);

  fclose(f);
}

/**
 * UI (I could write a separate file...)
 * To connect Contact with LinkeList.
 **/

void clearScreen() {
  system("clear");
}

int print_mainMenu() {
  int option;

  printf("1. Show all.\n2. Add a contact.\n3. Find contact.\n4. Delete contact.\n5. Edit contact.\n6. Import file.\n7. Export file.\n8. Average age.\n0. Exit.\n");
  scanf("%d", &option);

  return option;
}

Contact askFor_ContactData(Contact contact) {
  char buffer[50];

  printf("First name: ");
  scanf("%s", buffer);
  contact->firstName = convert_char_array_to_pointer(buffer);

  printf("Last name: ");
  scanf("%s", buffer);
  contact->lastName = convert_char_array_to_pointer(buffer);

  printf("Age: ");
  scanf("%d", &(contact->age));

  printf("Gender: ");
  scanf("%s", buffer);
  contact->gender = convert_char_array_to_pointer(buffer);

  printf("Phone (MUST be unique): ");
  scanf("%s", buffer);
  contact->phone = convert_char_array_to_pointer(buffer);

  printf("Email: ");
  scanf("%s", buffer);
  contact->email = convert_char_array_to_pointer(buffer);

  printf("Birthday: ");
  scanf("%s", buffer);
  contact->birthday = convert_char_array_to_pointer(buffer);

  return contact;
}

/**
 * MAIN
 **/

int main(int argc, char *argv[]) {
  LinkedList list = new_LinkedList();
  void *data;
  Contact contact;
  int option = -1;
  char buffer[50];

  while(option != 0) {
    clearScreen();
    option = print_mainMenu();
    getchar();

    switch(option) {
      case 1:
        clearScreen();
        forEach_LinkedList(list, print_Contact_wrapper);
        getchar();
        break;
      case 2:
        clearScreen();
        contact = new_Contact();
        contact = askFor_ContactData(contact);
        list = push_LinkedList(list, contact);
        break;
      case 3:
        clearScreen();
        printf("Phone: ");
        scanf("%s", buffer);
        getchar();
        data = find_LinkedList(list, compare_ContactPhoneByValue_wrapper, buffer);
        if (data) {
          print_Contact_wrapper(data, NULL);
        } else {
          printf("Not found.\n");
        }
        getchar();
        break;
      case 4:
        clearScreen();
        printf("Phone: ");
        scanf("%s", buffer);
        getchar();
        data = find_LinkedList(list, compare_ContactPhoneByValue_wrapper, buffer);
        if (data) {
          list = delete_LinkedList(list, data);
          contact = (Contact)data;
          free_Contact(contact);
          printf("Deleted contact.");
        } else {
          printf("Not found.\n");
        }
        getchar();
        break;
      case 5:
        clearScreen();
        printf("Phone: ");
        scanf("%s", buffer);
        getchar();
        data = find_LinkedList(list, compare_ContactPhoneByValue_wrapper, buffer);
        if (data) {
          contact = (Contact)data;
          contact = askFor_ContactData(contact);
        } else {
          printf("Not found.\n");
        }
        getchar();
        break;
      case 6:
        clearScreen();
        list = importContacts(list);
        printf("Done.\n");
        getchar();
        break;
      case 7:
        clearScreen();
        exportContacts(list);
        printf("Done.\n");
        getchar();
        break;
      case 8:
        clearScreen();
        if (isEmpty_LinkedList(list)) {
          printf("Empty.\n");
        } else {
          printf("Average age: %.2f\n", averageAge_Contacts(list));
        }
        getchar();
        break;
    }
  }

  forEach_LinkedList(list, free_Contact_wrapper, NULL);
  free_LinkedList(list);

  return 0;
}
