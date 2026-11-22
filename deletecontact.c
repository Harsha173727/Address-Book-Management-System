#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

// Confirms deletion and removes selected contact by shifting array elements left
static void deleteSelectedContact(AddressBook *addressBook, const int index[], int contactindex) 
{
    int actualIndex = index[contactindex];

    if (actualIndex < 0 || actualIndex >= addressBook->contactCount) 
    {
        printf("Error: Invalid contact selection.\n");
        return;
    }

    printf("\nYour selected contact details are shown below:\n");
    printf("-----------------------------------------------------------------------\n");
    printf(" %-25s %-15s %-30s\n", "NAME", "PHONE", "EMAIL");
    printf("-----------------------------------------------------------------------\n");
    printf(" %-25s %-15s %-30s\n", 
           addressBook->contacts[actualIndex].name,
           addressBook->contacts[actualIndex].phone,
           addressBook->contacts[actualIndex].email);
    printf("-----------------------------------------------------------------------\n");

    char ch;
    printf("Press 'Y' to confirm deletion: ");
    if (scanf(" %c", &ch) != 1) 
    {
        clearInputBuffer();
        printf("Deletion canceled.\n");
        return;
    }
    clearInputBuffer();

    // Remove element by shifting subsequent contacts
    if (ch == 'y' || ch == 'Y') 
    {
        for (int i = actualIndex; i < addressBook->contactCount - 1; i++) 
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;
        printf("Contact deleted successfully.\n");
        saveContactsToFile(addressBook);
    } 
    else 
    {
        printf("Deletion canceled. Contact was not deleted.\n");
    }
}

// Calls specific search functions (name, phone, email) for deletion
static int selectContactByCriteria(int choice, int *indexList, AddressBook *addressBook) 
{
    clearInputBuffer();

    switch (choice) 
    {
        case 1:
            printf("Selecting contact by name...\n");
            return Selected_byname_contact(indexList, addressBook);
        case 2:
            printf("Selecting contact by phone number...\n");
            return Selected_byphone_contact(indexList, addressBook);
        case 3:
            printf("Selecting contact by email...\n");
            return Selected_byemail_contact(indexList, addressBook);
        default:
            return 0;
    }
}

// Displays delete menu and guides user through contact removal
void deleteContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("Address book is empty. Nothing to delete.\n");
        return;
    }

    int index[addressBook->contactCount];
    int deleteChoice;

    do {
        printf("\n======== Select search criteria for contact deletion ========\n");
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("4. Exit from delete contact and save\n");
        printf("===========================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &deleteChoice) != 1) 
        {
            printf("Invalid choice. Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }

        if (deleteChoice >= 1 && deleteChoice <= 3) 
        {
            int selectedIndex = selectContactByCriteria(deleteChoice, index, addressBook);
            if (selectedIndex > 0) 
            {
                deleteSelectedContact(addressBook, index, selectedIndex - 1);
            }
        } 
        else if (deleteChoice == 4) 
        {
            printf("Exiting delete menu...\n\n");
            clearInputBuffer();
        } 
        else 
        {
            printf("Invalid search criteria selected.\n");
            clearInputBuffer();
        }

    } while (deleteChoice != 4);
}