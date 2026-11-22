#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Checks if substring exists inside haystack string ignoring case
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

// Menu for searching and displaying contacts matching partial name, phone, or email queries
void searchContact(AddressBook *addressBook) 
{
    int searchChoice;
    char query[30];

    do {
        printf("\n============Select search criteria:============\n");
        printf("1. search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n");
        printf("4. exited from search criteria\n");
        printf("================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &searchChoice) != 1) 
        { 
            printf("Invalid choice\nselect proper search criteria\n");
            clearInputBuffer();
            continue; 
        }

        switch (searchChoice) 
        {
            case 1: { // Substring search by name
                printf("searching based on name\n");
                printf("enter the name :");
                clearInputBuffer();
                scanf("%29[^\n]", query);

                int namecount = 0;
                printf("-----------------------------------------------------------------------\n");
                printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
                printf("-----------------------------------------------------------------------\n");

                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (containsIgnoreCase(addressBook->contacts[i].name, query)) {
                        printf("%-7d %-25s %-15s %-30s\n", namecount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        namecount++;
                    }     
                }
                if (namecount == 0) {
                    printf("searched name does not exist in the records\n");
                }
                break;
            }

            case 2: 
            { // Substring search by phone
                printf("searching based on phone no\n");
                printf("enter the phone no :");
                clearInputBuffer();
                scanf("%29[^\n]", query);

                int phonecount = 0;
                printf("-----------------------------------------------------------------------\n");
                printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
                printf("-----------------------------------------------------------------------\n");

                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (strstr(addressBook->contacts[i].phone, query) != NULL) 
                    {
                        printf("%-7d %-25s %-15s %-30s\n", phonecount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        phonecount++;
                    }  
                }
                if (phonecount == 0) 
                    printf("searched phone no does not exist in the records\n");

                break;
            }

            case 3: 
            { // Substring search by email
                printf("searching based on email\n");
                printf("enter the email:");
                clearInputBuffer();
                scanf("%29[^\n]", query);

                int emailcount = 0;
                printf("-----------------------------------------------------------------------\n");
                printf("%-7s %-25s %-15s %-30s\n", "S.NO", "NAME", "PHONE", "EMAIL");
                printf("-----------------------------------------------------------------------\n");

                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (containsIgnoreCase(addressBook->contacts[i].email, query)) 
                    {
                        printf("%-7d %-25s %-15s %-30s\n", emailcount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        emailcount++;
                    }
                }
                if (emailcount == 0) 
                    printf("searched email does not exist in the records\n");

                break;
            }

            case 4:
                printf("exited from the search contacts\n\n");
                break;

            default:
                printf("enter valid search criteria \n"); 
                break;
        }
    } while (searchChoice != 4);
}