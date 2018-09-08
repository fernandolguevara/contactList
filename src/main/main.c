#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

  writeInFile_Contact(contact, f);
}

int compare_Contact_wrapper(void* a, void* b, va_list ap) {
  Contact contactA = (Contact)a, contactB = (Contact)b;
  Compare_ContactFn compare_ContactFn = va_arg(ap, Compare_ContactFn);

  return compare_ContactFn(contactA, contactB);
}

/**
 * UTIL
 * Some utilities.
 **/

float averageAge_Contacts (LinkedList list) {
  /** 
   * I wanted to declare a reduce_LinkedList function, 
   * but the way it occured to me for returning any type wasn't nice (struct an enum)
   **/
  int sum = 0;
  Contact contact;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    contact = (Contact)(node->data);
    sum += contact->age;
  }

  /** 
   * I could calculate the length above but I like to module all the function
   * in cases where optimization is not needed.
   **/
  return ((float)sum)/length_LinkedList(list);
}

int maxAge_Contacts (LinkedList list) {
  int max = INT_MIN;
  Contact contact;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    contact = (Contact)(node->data);
    
    if (contact->age > max) {
      max = contact->age;
    }
  }

  return max;
}

int minAge_Contacts (LinkedList list) {
  int min = INT_MAX;
  Contact contact;

  for (LinkedNode *node = list; node != NULL; node = node->next) {
    contact = (Contact)(node->data);
    
    if (contact->age < min) {
      min = contact->age;
    }
  }

  return min;
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
 * UI
 **/

void clearScreen() {
  system("clear");
}

int print_mainMenu() {
  int option;

  clearScreen();

  printf("1. Show all.\n2. Add a contact.\n3. Find contact.\n4. Delete contact.\n5. Edit contact.\n6. Import file.\n7. Export file.\n8. Average age.\n9. Sort by attribute.\n10. Max age.\n11. Min age.\n0. Exit.\n");
  scanf("%d", &option);
  getchar();

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

void showAllContacts_screen(LinkedList list) {
  clearScreen();

  forEach_LinkedList(list, print_Contact_wrapper);

  getchar();
}

Contact addContact_screen() {
  Contact contact = new_Contact();

  clearScreen();

  return askFor_ContactData(contact);
}

void findContact_screen(LinkedList list) {
  char buffer[50];
  void *data;

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
}

LinkedList deleteContact_screen(LinkedList list) {
  char buffer[50];
  void *data;
  Contact contact;

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

  return list;
}

void editContact_screen(LinkedList list) {
  char buffer[50];
  void *data;
  Contact contact;
  
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
}

LinkedList importContacts_screen(LinkedList list) {
  clearScreen();

  list = importContacts(list);

  printf("Done.\n");
  getchar();

  return list;
}

void exportContacts_screen(LinkedList list) {
  clearScreen();

  exportContacts(list);

  printf("Done.\n");
  getchar();
}

void averageContactsAge_screen(LinkedList list) {
  clearScreen();

  if (isEmpty_LinkedList(list)) {
    printf("Empty.\n");
  } else {
    printf("Average age: %.2f\n", averageAge_Contacts(list));
  }

  getchar();
}

void sortContactsByAttribute_screen(LinkedList list) {
  int option;

  clearScreen();

  printf("1. First name.\n2. Last name.\n3. Age.\n4. Gender.\n5. Phone.\n6. Email.\n7. Birthday.\n");
  scanf("%d", &option);
  getchar();
  clearScreen();

  switch(option) {
    case 1:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByFirstName_Contact);
      break;
    case 2:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByLastName_Contact);
      break;
    case 3:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByAge_Contact);
      break;
    case 4:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByGender_Contact);
      break;
    case 5:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByPhone_Contact);
      break;
    case 6:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByEmail_Contact);
      break;
    case 7:
      bubbleSort_LinkedList(list, compare_Contact_wrapper, compareByBirthday_Contact);
      break;
  }

  forEach_LinkedList(list, print_Contact_wrapper);
  getchar();
}

void maxAge_screen(LinkedList list) {
  clearScreen();

  if (isEmpty_LinkedList(list)) {
    printf("Empty.\n");
  } else {
    printf("Max age: %d\n", maxAge_Contacts(list));
  }

  getchar();
}

void minAge_screen(LinkedList list) {
  clearScreen();

  if (isEmpty_LinkedList(list)) {
    printf("Empty.\n");
  } else {
    printf("Max age: %d\n", minAge_Contacts(list));
  }

  getchar();
}

/**
 * MAIN
 **/

int main(int argc, char *argv[]) {
  LinkedList list = new_LinkedList();
  int option = -1;

  while(option != 0) {
    option = print_mainMenu();

    switch(option) {
      case 1:
        showAllContacts_screen(list);
        break;
      case 2:
        list = push_LinkedList(list, addContact_screen());
        break;
      case 3:
        findContact_screen(list);
        break;
      case 4:
        list = deleteContact_screen(list);
        break;
      case 5:
        editContact_screen(list);
        break;
      case 6:
        list = importContacts_screen(list);
        break;
      case 7:
        exportContacts_screen(list);
        break;
      case 8:
        averageContactsAge_screen(list);
        break;
      case 9:
        sortContactsByAttribute_screen(list);
        break;
      case 10:
        maxAge_screen(list);
        break;
      case 11:
        minAge_screen(list);
        break;
    }
  }

  forEach_LinkedList(list, free_Contact_wrapper, NULL);
  free_LinkedList(list);

  return 0;
}
