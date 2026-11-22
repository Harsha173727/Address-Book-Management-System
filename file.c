#include <stdio.h>
#include <string.h>
#include "contact.h"

// Writes all contacts into contact.csv in CSV format
void saveContactsToFile(AddressBook *addressBook) 
{
    if (addressBook == NULL) return;

    FILE *fptr = fopen("contact.csv", "w");
    if (fptr == NULL) 
    {
        printf("Error: Could not open contact.csv for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("Contacts saved successfully!\n");
}

// Reads contact records from contact.csv into memory array
void loadContactsFromFile(AddressBook *addressBook) 
{
    if (addressBook == NULL) 
    return;

    FILE *fptr = fopen("contact.csv", "r");
    if (fptr == NULL) 
    {
        printf("contact.csv not found. Starting with empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }

    addressBook->contactCount = 0;

    // Read lines from CSV file into contact structs
    while (fscanf(fptr, " %49[^,],%49[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) 
    {
        addressBook->contactCount++;
    }

    fclose(fptr);
}