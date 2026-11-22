#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

// Clears leftover characters from standard input stream to prevent input errors
void clearInputBuffer(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Resets contact count and loads saved entries from file on startup
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

// Saves current contacts to file and immediately exits the program
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);
    exit(0);
}

// Default hardcoded sample contacts for testing
static const Contact dummyContacts[] = 
{
    {"John Doe",     "1234567890", "john@example.com"},
    {"Alice Smith",  "0987654321", "alice@example.com"},
    {"Bob Johnson",  "1112223333", "bob@company.com"},
    {"Carol White",  "4445556666", "carol@company.com"},
    {"David Brown",  "7778889999", "david@example.com"},
    {"Eve Davis",    "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis",    "8889990000", "ian@example.com"}
};

// Fills address book memory with pre-defined dummy contacts up to capacity limit
void populateAddressBook(AddressBook *addressBook) 
{
    if (addressBook == NULL) 
    return;

    int numDummyContacts = (int)(sizeof(dummyContacts) / sizeof(dummyContacts[0]));

    // Copy each dummy contact into main memory array
    for (int i = 0; i < numDummyContacts; i++) 
    {
        if (addressBook->contactCount >= MAX_CONTACTS) 
        {
            printf("Warning: Maximum contact limit (%d) reached. Stopping population.\n", MAX_CONTACTS);
            break;
        }

        addressBook->contacts[addressBook->contactCount] = dummyContacts[i];
        addressBook->contactCount++;
    }
}