#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Helper function to perform case-insensitive substring search
static int containsIgnoreCase(const char *haystack, const char *needle) 
{
    while (*haystack) 
    {
        const char *h = haystack;
        const char *n = needle;
        
        while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) 
        {
            h++;
            n++;
        }
        if (!*n) 
        return 1;

        haystack++;
    }
    return 0;
}

// Searches contacts by name, prints matching choices, and gets user selection
int Selected_byname_contact(int index[], AddressBook *addressBook) 
{
    char ch[100];
    printf("Enter the name : ");
    scanf(" %[^\n]", ch);

    int namecount = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (containsIgnoreCase(addressBook->contacts[i].name, ch)) 
        {
            index[namecount] = i;
            namecount++;
        }
    }

    if (namecount == 0) 
    {
        printf("The name was not found in the records\n");
        return 0;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < namecount; i++) 
    {
        printf("%-7d %-25s %-15s %-30s\n", 
               i + 1, 
               addressBook->contacts[index[i]].name, 
               addressBook->contacts[index[i]].phone, 
               addressBook->contacts[index[i]].email);
    }
    printf("-----------------------------------------------------------------------\n");

    if (namecount == 1) 
    {
        printf("only one contact is present with %s name\n", ch);
        return namecount;
    }

    int selectedcontact;
    printf("select the contact in the above list based on serial no : ");
    scanf("%d", &selectedcontact);

    if (selectedcontact > namecount || selectedcontact < 1) 
    {
        printf("Invalid selection\n");
        return 0;
    }

    return selectedcontact;
}

// Searches contacts by phone, lists matching records, and gets user selection
int Selected_byphone_contact(int index[], AddressBook *addressBook) 
{
    char ch[100];
    printf("Enter the phone no : ");
    scanf(" %s", ch);

    int phonecount = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strstr(addressBook->contacts[i].phone, ch) != NULL) 
        {
            index[phonecount] = i;
            phonecount++;
        }
    }

    if (phonecount == 0) 
    {
        printf("searched phone no does not exist in the records\n");
        return 0;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < phonecount; i++) 
    {
        printf("%-7d %-25s %-15s %-30s\n", 
               i + 1, 
               addressBook->contacts[index[i]].name, 
               addressBook->contacts[index[i]].phone, 
               addressBook->contacts[index[i]].email);
    }
    printf("-----------------------------------------------------------------------\n");

    if (phonecount == 1) 
    {
        printf("only one contact is present with %s phone number\n", ch);
        return phonecount;
    }

    int selectedcontact;
    printf("select the contact in above list based on serial no : ");
    scanf("%d", &selectedcontact);

    if (selectedcontact > phonecount || selectedcontact < 1) 
    {
        printf("Invalid selection\n");
        return 0;
    }

    return selectedcontact;
}

// Searches contacts by email, displays matching options, and returns user selection
int Selected_byemail_contact(int index[], AddressBook *addressBook) 
{
    char ch[100];
    printf("Enter the email : ");
    scanf(" %s", ch);

    int emailcount = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (containsIgnoreCase(addressBook->contacts[i].email, ch)) 
        {
            index[emailcount] = i;
            emailcount++;
        }
    }

    if (emailcount == 0) 
    {
        printf("searched email does not exist in the records\n");
        return 0;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < emailcount; i++) 
    {
        printf("%-7d %-25s %-15s %-30s\n", 
               i + 1, 
               addressBook->contacts[index[i]].name, 
               addressBook->contacts[index[i]].phone, 
               addressBook->contacts[index[i]].email);
    }
    printf("-----------------------------------------------------------------------\n");

    if (emailcount == 1) 
    {
        printf("only one contact is present with %s email\n", ch);
        return emailcount;
    }

    int selectedcontact;
    printf("select the contact in the above list based on serial no : ");
    scanf("%d", &selectedcontact);

    if (selectedcontact > emailcount || selectedcontact < 1) 
    {
        printf("Invalid selection\n");
        return 0;
    }

    return selectedcontact;
}