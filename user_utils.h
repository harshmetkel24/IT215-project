#include "start.h"

void addUser(char user_id[], char password[])
{
    FILE *fp = fopen("./user_info.csv", "a+");
    if (fp == NULL)
    {
        printf("Unable to open user_info.csv.\n");
        return;
    }
    fprintf(fp, "%s, %s\n", user_id, password);
    printf("New User Added Successfully :)\n");
    fclose(fp);
}

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

int verifyUser(char user_id[], char password[])
{
    FILE *fp = fopen("./user_info.csv", "r");
    if (fp == NULL)
    {
        printf("Unable to open user_info.csv.\n");
        return 0;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fp))
    {
        column = 0;
        ++row;
        if (row == 1)
            continue;                           // avoid printing the name of column
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            ++column;
            if (column == 1)
            {
                // if user with user_id found
                if (!strcmp(row_string, user_id))
                {
                    flag = true;
                }
            }
            else if (flag && column == 2)
            {
                fclose(fp);
                row_string = trim(row_string);
                printf("%s", row_string);
                if (!strcmp(row_string, password))
                {
                    return true;
                }
                else
                {
                    printf("Password didn't matched!\n");
                    return false;
                }
            }
            row_string = strtok(NULL, ",");
        }
        printf("\n");
    }
    fclose(fp);
    printf("No user found with USER ID %s.\n", user_id);
    return false;
}

void printUserInfo()
{
    FILE *fp = fopen("./user_info.csv", "r");
    if (fp == NULL)
    {
        printf("Unable to open user_info.csv.\n");
        return;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    while (fgets(buffer, STR_LEN, fp))
    {
        column = 0;
        ++row;
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            printf("%s\t", row_string);
            row_string = strtok(NULL, ",");
            ++column;
        }
        printf("\n");
    }
    fclose(fp);
}
