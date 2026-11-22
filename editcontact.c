#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

// Sub-menu to update name, phone, or email of selected contact
static void selectededitcontact(AddressBook *addressBook, const int index[], int selectedcontact) 
{
    int actualIndex = index[selectedcontact];
    int choice;
    char temp[NAME_LEN];

    do {
        printf("\nEditing contact: %s\n", addressBook->contacts[actualIndex].name);
        printf("1. Edit Name\n");
        printf("2. Edit Phone\n");
        printf("3. Edit Email\n");
        printf("4. Done Editing\n");
        printf("\nEnter option: ");

        if (scanf("%d", &choice) != 1) 
        {
            clearInputBuffer();
            continue;
        }

        switch (choice) 
        {
            case 1:
                printf("Enter new name: ");
                scanf(" %[^\n]", temp);
                clearInputBuffer();
                if (validateName(temp)) 
                {
                    strcpy(addressBook->contacts[actualIndex].name, temp);
                    printf("Name updated successfully!\n");
                    saveContactsToFile(addressBook);
                }
                break;

            case 2:
                printf("Enter new phone: ");
                scanf(" %[^\n]", temp);
                clearInputBuffer();
                if (validatePhone(addressBook, temp)) 
                {
                    strcpy(addressBook->contacts[actualIndex].phone, temp);
                    printf("Phone updated successfully!\n");
                    saveContactsToFile(addressBook);
                }
                break;

            case 3:
                printf("Enter new email: ");
                scanf(" %[^\n]", temp);
                clearInputBuffer();
                if (validateEmail(addressBook, temp)) 
                {
                    strcpy(addressBook->contacts[actualIndex].email, temp);
                    printf("Email updated successfully!\n");
                    saveContactsToFile(addressBook);
                }
                break;

            case 4:
                printf("Finished editing contact.\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);
}

// Calls specific search functions (name, phone, email) for editing
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

// Menu for searching and selecting a contact to modify
void editContact(AddressBook *addressBook) 
{
    int index[addressBook->contactCount];
    int editChoice;

    do {
        printf("\n====== Select search criteria for contact editing =====\n");
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("4. Exit from edit contact\n");
        printf("======================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &editChoice) != 1) 
        {
            printf("Invalid choice. Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }

        if (editChoice >= 1 && editChoice <= 3) 
        {
            int selectedIndex = selectContactByCriteria(editChoice, index, addressBook);
            if (selectedIndex > 0) 
            {
                selectededitcontact(addressBook, index, selectedIndex - 1);
            }
        } 
        else if (editChoice == 4) 
        {
            printf("Exiting edit contact menu...\n\n");
            clearInputBuffer();
        } 
        else 
        {
            printf("Invalid search criteria selected.\n");
            clearInputBuffer();
        }

    } while (editChoice != 4);
}