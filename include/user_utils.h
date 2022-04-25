#include "start.h"

struct User
{
    char user_id[STR_LEN], password[STR_LEN], contact_no[STR_LEN];
};

void addUser(struct User user);
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
int verifyUser(char user_id[], char password[]);
void printUserInfo();
