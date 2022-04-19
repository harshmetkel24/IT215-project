#include "start.h"
#include "user_utils.h"

void addUser(struct User user)
{
    FILE *fp = fopen("./user_info.csv", "a+");
    if (fp == NULL)
    {
        printf("Unable to open user_info.csv.\n");
        return;
    }
    fprintf(fp, "%s, %s, %s\n", user.user_id, user.password, user.contact_no);
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
            continue;                           // avoid printing the names of column
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

int main()
{
    printf("Welcome to Courier System.\n\n");
    int loop = 1;
    while (loop)
    {
        printf("Please select correct option from below:\n\n");
        printf("1) Admin\n2) User\n");
        // role = 1 => Admin login
        // role = 2 => User
        int role;
        scanf("%d", &role);
        switch (role)
        {
        case 1:
        {
            int admin_login = 1;
            while (admin_login)
            {
                printf("Admin Login Credentials:\n\n");
                printf("Please Enter User ID for Admin: ");
                char user_id[STR_LEN];
                scanf("%s", user_id);
                printf("Please Enter Password for Admin: ");
                char password[STR_LEN];
                scanf("%s", password);
                char admin_id[] = "admin";
                char admin_password[] = "admin@123";
                if (!strcmp(admin_password, password) && !strcmp(admin_id, user_id))
                {
                    admin_login = 0;
                    getch();
                    system("cls"); // clears the screen
                    printf("Welcome to Admin Dashboard:\n\n");
                    printUserInfo();
                }
                else
                    printf("You entered wrong Credentials. Check again!\n");
            }
            loop = 0;
            break;
        }
        case 2:
        {
            int user_reg = 1;
            while (user_reg)
            {
                int registered;
                printf("Already registered?\nPress 1 for Yes or 0 for No\n");
                scanf("%d", &registered);
                // already registered means user login
                if (registered == 1)
                {
                    int user_login = 1;
                    while (user_login)
                    {
                        printf("User Login:\n\n");
                        printf("Please enter your User ID: ");
                        char user_id[STR_LEN], password[STR_LEN];
                        scanf("%s", user_id);
                        printf("Please enter your User Password: ");
                        scanf("%s", password);
                        // need to read this from csv file using file handling
                        char original_id[] = "user", original_pwd[] = "user";
                        if (verifyUser(user_id, password))
                        {
                            // verifyUser(user_id, password);
                            printf("User Logged in successfully :)\n");
                            getch();
                            user_login = 0;
                        }
                    }
                    user_reg = 0;
                }
                // not registered so register new user
                else if (registered == 0)
                {
                    int user_register = 1;
                    while (user_register)
                    {
                        printf("User Registration: \n\n");
                        printf("Please enter your User ID: ");
                        char user_id[STR_LEN];
                        scanf("%s", user_id);
                        char contact_no[STR_LEN];
                        printf("Please enter your Contact Number: ");
                        scanf("%s", contact_no);
                        char password[STR_LEN];
                        printf("Please enter your Password: ");
                        scanf("%s", password);
                        char confirm_password[STR_LEN];
                        printf("Please confirm your Password: ");
                        scanf("%s", confirm_password);
                        if (!strcmp(confirm_password, password))
                        {
                            struct User user;
                            strcpy(user.user_id, user_id);
                            strcpy(user.password, password);
                            strcpy(user.contact_no, contact_no);
                            addUser(user);
                            printf("User with User ID %s is registered successfully :)\n", user_id);
                            user_register = 0;
                            getch();
                        }
                        else
                        {
                            printf("Password didn't match! Try again\n");
                        }
                    }
                    user_reg = 0;
                }
                else
                {
                    printf("Entered wrong option please select again.\n");
                    continue;
                }
            }
            loop = 0;
            break;
        }
        default:
            printf("Entered wrong no\n");
            break;
        }
    }
    return 0;
}