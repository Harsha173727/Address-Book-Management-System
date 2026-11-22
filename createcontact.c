#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

// Prompts input for name, phone, email, validates them, and saves new contact
void createContact(AddressBook *addressBook) 
{
    char answer[10];

    do {
        // Prevent creation if limit is reached
        if (addressBook->contactCount >= MAX_CONTACTS) 
        {
            printf("\nError: Address book is full (Maximum %d contacts allowed).\n", MAX_CONTACTS);
            return;
        }

        Contact *newContact = &addressBook->contacts[addressBook->contactCount];

        // Loop until a valid name is provided
        printf("\n%-25s: ", "Enter name");
        while (1) 
        {
            scanf(" %[^\n]", newContact->name);
            clearInputBuffer();

            if (validateName(newContact->name))
            break;

            printf("%-25s: ", "Enter name again");
        }

        // Loop until a valid phone number is provided
        printf("%-25s: ", "Enter phone number");
        while (1) 
        {
            scanf(" %[^\n]", newContact->phone);
            clearInputBuffer();

            if (validatePhone(addressBook, newContact->phone))
                break;
        
            printf("%-25s: ", "Enter phone number again");
        }

        // Loop until a valid email is provided
        printf("%-25s: ", "Enter email ID");
        while (1) 
        {
            scanf(" %[^\n]", newContact->email);
            clearInputBuffer();

            if (validateEmail(addressBook, newContact->email)) 
                break;

            printf("%-25s: ", "Enter email again");
        }

        addressBook->contactCount++;

        printf("\n-------- Contact no %d successfully created ---------\n", addressBook->contactCount);
        saveContactsToFile(addressBook);

        // Ask if user wants to add another contact
        do 
        {
            printf("\nCreate another contact? (yes/no): ");
            if (scanf("%9s", answer) != 1) 
            {
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();

            if (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0) 
                printf("Invalid response. Please enter 'yes' or 'no'.\n");

        } while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0);

    } while (strcmp(answer, "yes") == 0);
}