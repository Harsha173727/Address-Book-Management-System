#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Compares two strings alphabetically ignoring upper/lower case
static int compareIgnoreCase(const char *s1, const char *s2) 
{
    while (*s1 && *s2) 
    {
        int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);

        if (diff != 0) 
        return diff;
        
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

// Returns pointer to name, phone, or email string based on sort option
static const char* getContactField(const Contact *contact, int sortCriteria) 
{
    if (sortCriteria == 1) 
        return contact->name;

    if (sortCriteria == 2) 
        return contact->phone;

    if (sortCriteria == 3) 
        return contact->email;

    return NULL;
}

// Sorts contacts using Bubble Sort by chosen field and prints formatted list
void listContacts(AddressBook *addressBook) 
{
    if (addressBook == NULL || addressBook->contactCount == 0) 
    {
        printf("\nNo contacts available in the address book.\n");
        return;
    }

    int sortChoice = 0;
    printf("\nSelect sort criteria:\n");
    printf("==========================\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("===========================\n");
    printf("Enter your choice: ");

    if (scanf("%d", &sortChoice) != 1) 
    {
        printf("Invalid choice input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (sortChoice < 1 || sortChoice > 3) 
    {
        printf("Invalid sorting option. Please select a choice between 1 and 3.\n");
        return;
    }

    const char *headers[] = {"Name", "Phone Number", "Email"};
    printf("\n========================== Contacts Sorted by %s ==========================\n\n", headers[sortChoice - 1]);

    // Bubble sort contacts array
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            const char *fieldA = getContactField(&addressBook->contacts[j], sortChoice);
            const char *fieldB = getContactField(&addressBook->contacts[j + 1], sortChoice);

            if (compareIgnoreCase(fieldA, fieldB) > 0) 
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print header and formatted contact rows
    printf("-----------------------------------------------------------------------\n");
    printf("%-7s %-20s %-15s %-30s\n", "INDEX", "NAME", "PHONE", "EMAIL ID");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-7d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-----------------------------------------------------------------------\n");
    printf("Total Contacts : %d\n", addressBook->contactCount);
}