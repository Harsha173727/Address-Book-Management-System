/* Standard Project Header Documentation */
/*
Name            : B.Harsha Vardhan
student id      : 26015_135
batch id        : 26015C
start Date      : 31/07/2026
end date        : 09/08/2026

Description     : This Address Book project is a C-based command-line application that manages contacts 
                  through full create, search, edit, delete, and sorted listing operations. 
                  It features strict input validation for names, 10-digit phone numbers, and email formats, 
                  along with persistent file storage using a CSV file to automatically save and load user records.
*/

#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

// Main entry point that displays menu and routes user selections
int main(void) 
{
    int choice = 0;
    AddressBook addressBook;

    // Load initial contacts from file at startup
    initialize(&addressBook);

    // Main interactive control menu loop
    do {
        printf("\n==============Address Book Menu:===============\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("7. Exit\n");
        printf("================================================\n");
        printf("Enter your choice: ");

        // Read and validate numeric menu choice
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        // Route selection to corresponding functionality
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                if (addressBook.contactCount > 0) 
                    editContact(&addressBook);
                else
                    printf("No contacts found. Address book is empty.\n");
                break;

            case 4:
                if (addressBook.contactCount > 0)
                    deleteContact(&addressBook);
                else
                    printf("No contacts found. Address book is empty.\n");
                break;

            case 5:
                if (addressBook.contactCount > 0)
                    listContacts(&addressBook);
                else
                    printf("No contacts found. Address book is empty.\n");
                break;

            case 6:
                if (addressBook.contactCount > 0) 
                {
                    printf("Saving contacts and exiting...\n");
                    saveContactsToFile(&addressBook);
                } 
                else
                    printf("Exiting... (Address book is empty, no file changes made).\n");
                break;
            case 7:
                printf("Exiting without Saving!\n");
                exit(0);

            default:
                printf("Invalid choice. Please choose an option between 1 and 6.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}
