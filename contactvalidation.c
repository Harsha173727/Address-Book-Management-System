#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Validates name for length >=4, alphabets only, and no consecutive spaces
int validateName(const char *name) 
{
    if (name[0] == ' ') 
    {
        printf("Error: Name cannot start with a space.\n");
        return 0;
    }

    int len = strlen(name);
    if (len < 4) 
    {
        printf("Error: Name must contain at least 4 characters.\n");
        return 0;
    }

    for (int i = 0; i < len; i++) 
    {
        unsigned char c = (unsigned char)name[i];

        if (!isalpha(c) && c != ' ') 
        {
            printf("Error: Name must contain only alphabets and single spaces.\n");
            return 0;
        }

        if (c == ' ' && name[i + 1] == ' ') 
        {
            printf("Error: Name cannot contain consecutive spaces.\n");
            return 0;
        }
    }

    return 1;
}

// Validates phone number for exactly 10 digits, starting 6-9, and uniqueness
int validatePhone(const AddressBook *addressBook, const char *phone) 
{
    int len = strlen(phone);

    if (len != 10) 
    {
        printf("Error: Phone number must contain exactly 10 digits.\n");
        return 0;
    }

    if (phone[0] < '6' || phone[0] > '9') 
    {
        printf("Error: The first digit must be between 6 and 9.\n");
        return 0;
    }

    for (int i = 0; i < len; i++) 
    {
        if (!isdigit((unsigned char)phone[i])) 
        {
            printf("Error: Phone number must contain digits only.\n");
            return 0;
        }
    }

    // Check if phone number is already registered
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
        {
            printf("Error: Phone number already exists. It must be unique.\n");
            return 0;
        }
    }
    return 1;
}

// Validates email for lowercase start, single '@' and '.', correct domain, and uniqueness
int validateEmail(const AddressBook *addressBook, const char *email) 
{
    int at_count = 0;
    int dot_count = 0;
    int at_position = -1;
    int dot_position = -1;
    int len = strlen(email);

    if (len == 0) 
    {
        printf("Error: Email cannot be empty.\n");
        return 0;
    }

    if (!islower((unsigned char)email[0])) 
    {
        printf("Error: Email must start with a lowercase letter.\n");
        return 0;
    }

    for (int i = 0; i < len; i++) 
    {
        if (email[i] == '@') 
        {
            at_count++;
            at_position = i;
        } 
        else if (email[i] == '.') 
        {
            dot_count++;
            dot_position = i;
        }
    }

    if (at_count != 1) 
    {
        printf("Error: Email must contain exactly one '@' symbol.\n");
        return 0;
    }

    if (dot_count != 1) 
    {
        printf("Error: Email must contain exactly one '.' symbol.\n");
        return 0;
    }

    if (dot_position < at_position) 
    {
        printf("Error: Dot (.) must come after the '@' symbol.\n");
        return 0;
    }

    for (int i = 0; i < at_position; i++) 
    {
        unsigned char c = (unsigned char)email[i];
        if (!islower(c) && !isdigit(c)) 
        {
            printf("Error: Username before '@' can only contain lowercase letters and digits.\n");
            return 0;
        }
    }

    if (!isalnum((unsigned char)email[at_position - 1])) 
    {
        printf("Error: The character right before '@' must be a letter or digit.\n");
        return 0;
    }

    if (dot_position == at_position + 1) 
    {
        printf("Error: Domain name between '@' and '.' cannot be empty.\n");
        return 0;
    }

    for (int i = at_position + 1; i < len; i++) 
    {
        if (email[i] == '.') 
        continue;
        
        if (!islower((unsigned char)email[i])) 
        {
            printf("Error: Only lowercase letters are allowed in domain structure.\n");
            return 0;
        }
    }

    const char *extension = email + dot_position;
    if (strcmp(extension, ".com") != 0 && strcmp(extension, ".in") != 0) 
    {
        printf("Error: Invalid extension. Email must end strictly with '.com' or '.in'.\n");
        return 0;
    }

    // Check if email already exists
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) 
        {
            printf("Error: Email address already exists. It must be unique.\n");
            return 0;
        }
    }

    return 1;
}