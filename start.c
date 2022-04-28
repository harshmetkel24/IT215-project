#include "./include/start.h"
#include "./include/user_utils.h"

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
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            ++column;
            if (column == 1)
            {
                // if user with user_id found
                row_string = trim(row_string);
                if (!strcmp(row_string, user_id))
                {
                    flag = true;
                }
            }
            else if (flag && column == 2)
            {
                fclose(fp);
                row_string = trim(row_string);
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
        if (row == 1)
        {
            printf("user_id, contact_no\n\n");
            continue;
        }
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            if (column == 0)
                printf("%s, ", row_string);
            else if (column == 2)
                printf("%s", row_string);
            row_string = strtok(NULL, ",");
            ++column;
        }
        printf("\n");
    }
    fclose(fp);
}

void printCourierInfo()
{
    FILE *fp = fopen("./courier_info.csv", "r");
    if (fp == NULL)
    {
        printf("Unable to open csv file of courier!!\n");
        return;
    }
    char buffer[STR_LEN];
    int row = 0, column = 0;
    int flag = false;
    while (fgets(buffer, STR_LEN, fp))
    {
        column = 0;
        ++row;
        if (row == 1)
        {
            printf("Courier ID, Sender, Sender mob, Receiver, Receiver mob, Receiver Address,  Message,  Courrier Status\n\n");
            continue;
        }
        char *row_string = strtok(buffer, ","); // splitting around
        while (row_string)
        {
            ++column;
            if (column != 9)
                printf("%s, ", row_string);
            else
                printf("%s", row_string);
            row_string = strtok(NULL, ",");
        }
    }
    fclose(fp);
}

void useExec()
{
    int pid1 = fork();
    if (pid1 == 0)
    {
        char *prog = "gcc";
        int pid2 = fork();
        if (pid2 == 0)
        {

            int pid3 = fork();
            if (pid3 == 0)
            {
                int pid4 = fork();
                if (pid4 == 0)
                {
                    execlp(prog, prog, "-c", "courier_functions.c", "-o", "courier_functions.o", NULL);
                }
                else
                {
                    wait(NULL);
                    execlp("ar", "ar", "rcs", "./lib/libcourier.a", "courier_functions.o", NULL);
                }
            }
            else
            {
                wait(NULL);
                execlp(prog, prog, "-c", "courier_info.c", "-o", "courier_info.o", NULL);
            }
        }
        else
        {
            wait(NULL);
            execlp(prog, prog, "-o", "courier_info", "courier_info.o", "-L./lib", "-lcourier", "-pthread", NULL);
        }
    }
    else
    {
        wait(NULL);
        char *run = "./courier_info";
        execlp(run, run, NULL);
    }
}

void startExec()
{
    int pid;
    pid = fork();
    if (pid == 0)
    { // child process will compile the file courier_info.c;
        char *prog = "gcc";
        char *arg1 = "start.c";
        char *arg2 = "-o";
        char *arg3 = "start.out";
        execlp(prog, prog, arg1, arg2, arg3, NULL);
    }
    else
    { // parent will wait for child to compile file then it will execute the file;
        int childPid, status;
        childPid = wait(&status);
        char *run = "./start.out";
        execlp(run, run, NULL);
    }
}

int main()
{
    system("clear"); // clears the screen
    printf("**********************************************\n");
    printf("*                                            *\n");
    printf("*       Welcome to Courier System            *\n");
    printf("*                                            *\n");
    printf("**********************************************\n");
    int loop = 1;
    while (loop)
    {
        printf("**********************************************\n");
        printf("Please select correct option from below:\n\n");
        printf("Enter 1 if you are an Admin\nEnter 2 if you are an User\n");
        printf("**********************************************\n");

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
                system("clear"); // clears the screen
                printf("Admin Login Credentials:\n\n");
                getchar();
                printf("Please Enter User ID for Admin: ");
                char user_id[STR_LEN];
                scanf("%[^\n]s", user_id);
                getchar();
                printf("Please Enter Password for Admin: ");
                char password[STR_LEN];
                scanf("%[^\n]s", password);
                char admin_id[] = "admin";
                char admin_password[] = "admin@123";
                if (!strcmp(admin_password, password) && !strcmp(admin_id, user_id))
                {
                    admin_login = 0;
                    getchar();
                    printf("Welcome to Admin Dashboard:\n\n");
                    printf("All User Details:\n\n");
                    printUserInfo();
                    printf("All Courier Details:\n\n");
                    printCourierInfo();
                }
                else
                    printf("You entered wrong Credentials. Check again!\n");
                getchar();
                system("clear"); // clears the screen
                startExec();
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
                system("clear"); // clears the screen
                printf("Are you already registered?\n\nPress 1 for Yes or 0 for No\n");
                scanf("%d", &registered);
                // already registered means user login
                if (registered == 1)
                {
                    int user_login = 1;
                    while (user_login)
                    {
                        printf("**********************************************\n");
                        printf("User Login:\n");
                        printf("**********************************************\n");
                        getchar();
                        printf("Please enter your User ID: ");
                        char user_id[STR_LEN], password[STR_LEN];
                        scanf("%[^\n]s", user_id);
                        getchar();
                        printf("Please enter your User Password: ");
                        scanf("%[^\n]s", password);
                        // need to read this from csv file using file handling
                        if (verifyUser(user_id, password))
                        {
                            printf("User Logged in successfully :)\n");
                            user_login = 0;
                            getchar();
                            system("clear"); // clears the screen
                            useExec();
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
                        getchar();
                        printf("Please enter your User ID: ");
                        char user_id[STR_LEN];
                        scanf("%[^\n]s", user_id);
                        char contact_no[STR_LEN];
                        getchar();
                        printf("Please enter your Contact Number: ");
                        scanf("%[^\n]s", contact_no);
                        char password[STR_LEN];
                        getchar();
                        printf("Please enter your Password: ");
                        scanf("%[^\n]s", password);
                        getchar();
                        char confirm_password[STR_LEN];
                        printf("Please confirm your Password: ");
                        scanf("%[^\n]s", confirm_password);
                        if (!strcmp(confirm_password, password))
                        {
                            struct User user;
                            strcpy(user.user_id, user_id);
                            strcpy(user.password, password);
                            strcpy(user.contact_no, contact_no);
                            addUser(user);
                            printf("User with User ID %s is registered successfully :)\n", user_id);
                            user_register = 0;
                            getchar();
                            useExec();
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